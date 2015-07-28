#!/usr/bin/env perl
use List::Util qw(reduce);
use Data::Dumper;
use sexpr;
use warnings;
use strict;

# This script takes the tiler grammar file (x64.tiles)
# and produces tiler tables.

# Collect rules -> form list, table;
# list contains 'shallow' nodes, maps rulenr -> rule
# indirectly create rulenr -> terminal
# table contains head -> rulenr

my @rules;

sub add_rule {
    my ($fragment, $terminal, $cost, $depth) = @_;
    my $list = [];
    # replace all sublist with pseudorules
    for my $item (@$fragment) {
        if (ref($item) eq 'ARRAY') {
            # create pseudorule
            my $label = sprintf('L%dP%d', scalar @rules, ++$depth);
            # divide costs
            $cost /= 2;
            add_rule($item, $label, $cost, $depth);
            push @$list, $label;
        } else {
            push @$list, $item;
        }
    }
    # NB - only top-level fragments are associated with tiles.
    my $rulenr = scalar @rules;
    push @rules, [$list, $terminal, $cost];
}


my $parser = sexpr->parser(\*DATA);
while (my $tree = $parser->read) {
    my $keyword = shift @$tree;
    if ($keyword eq 'tile:') {
        add_rule($tree->[0], $tree->[1], $tree->[2], 1);
    }
}

# generate topological graph
my (%heads, %deps, %block);
for (my $rule_nr = 0; $rule_nr < @rules; $rule_nr++) {
    my $frag = $rules[$rule_nr][0];
    my $head = $frag->[0];
    my $term = $rules[$rule_nr][1];
    push @{$heads{$head}}, $rule_nr;
    for (my $i = 1; $i < @$frag; $i++) {
        my $item = $frag->[$i];
        if ($item ne $term) {
            # add dependency to resolution of term
            push @{$deps{$item}}, $rule_nr;
            $block{$head}->{$item}++;
        }
    }
}


my @order;
my %candidates;
my @rulesets;
my %inversed;
for my $head (keys %heads) {
    push @order, $head unless $block{$head};
}

while (@order) {
    my $head = shift @order;
    print "Generating rulesets for $head\n";
    my $rule_nrs = $heads{$head};
    # hold map of head,ruleset,ruleset -> rules
    my %table;
    # construct all applicable rules based on the current known rulesets
    for my $rule_nr (@$rule_nrs) {
        my ($c1, $c2) = @{$rules[$rule_nr][0]}[1,2];
        if (defined $c2) {
            for my $rs1 (@{$candidates{$c1}}) {
                for my $rs2 (@{$candidates{$c2}}) {
                    $table{$head,$rs1,$rs2}->{$rule_nr} = 1;
                }
            }
        } elsif (defined $c1) {
            for my $rs1 (@{$candidates{$c1}}) {
                $table{$head,$rs1,-1}->{$rule_nr} = 1;
            }
        } else {
            $table{$head,-1,-1}->{$rule_nr} = 1;
        }
    }
    # now add all distinct sets of rules to the rule sets
    print "Rulesets for $head: ";
    my %provided;
    for my $generated (values %table) {
        my @rule_nrs = sort keys %$generated;
        my $key = join $;, @rule_nrs;
        next if defined $inversed{$key};
        my @terms = map { $rules[$_][1] } @rule_nrs;
        my $ruleset_nr = scalar @rulesets;
        push @rulesets, [@rule_nrs];
        $inversed{$key} = $ruleset_nr;
        print '(', join ', ', @rule_nrs, '); ';
        for (@terms) {
            push @{$candidates{$_}}, $ruleset_nr;
            $provided{$_} = 1;
        }
    }
    print "\n";

    # Unblock the waiting elements.
    for my $term (keys %provided) {
        next unless defined $deps{$term};
        for (my $i = 0; $i < @{$deps{$term}}; $i++) {
            my $rule = $deps{$term}[$i];
            my $head = $rules[$rule][0][0];
            next unless $block{$head}{$term};
            delete $block{$head}{$term};
            if (!%{$block{$head}}) {
                push @order, $head;
                delete $block{$head};
            }
        }
        delete $deps{$term};
    }
}


print "Now we have ", scalar @rulesets, " different rulesets\n";


# Calculate minimum cost rule out of a ruleset and a terminal
sub min_cost {
    my ($ruleset_nr, $term) = @_;
    my @applicable = grep { $rules[$_][1] eq $term } @{$rulesets[$ruleset_nr]};
    my $min = reduce { $rules[$a][2] < $rules[$b][2] ? $a : $b } @applicable;
    return $min;
}

# Generate a table, indexed by head, ruleset_nr, ruleset_nr -> ruleset
# and another table, head, ruleset_nr, ruleset_nr -> rule
my %table;
my %trans;
for (my $rule_nr = 0; $rule_nr < @rules; $rule_nr++) {
    my ($frag, $term, $cost) = @{$rules[$rule_nr]};
    my ($head, $c1, $c2)     = @$frag;
    if (defined $c1) {
        my $cand1 = $candidates{$c1};
        if (defined $c2) {
            # binary
            my $cand2   = $candidates{$c2};
            for my $rs1 (@$cand1) {
                my $lc1 = min_cost($rs1, $c1);
                for my $rs2 (@$cand2) {
                    my $lc2 = min_cost($rs2, $c2);
                    $table{$head}{$rs1}{$rs2} = [$rule_nr, $lc1, $lc2] if $term eq 'reg';
                    $trans{$head,$rs1,$rs2}->{$rule_nr} = 1;
                }
            }
        } else {
            # unary
            for my $rs1 (@$cand1) {
                my $lc1 = min_cost($rs1, $c1);
                $table{$head}{$rs1} = [$rule_nr, $lc1] if $term eq 'reg';
                $trans{$head,$rs1}->{$rule_nr} = 1;
            }
        }
    } else {
        # no children
        $table{$head} = [$rule_nr] if $term eq 'reg';
        $trans{$head}->{$rule_nr} = 1;
    }
}

# translate rule lists to rulesets
my %states;
while (my ($table_key, $applicable) = each(%trans)) {
    my @rule_nrs = sort keys %$applicable;
    my $ruleset_key = join($;, @rule_nrs);
    my $ruleset_nr  = $inversed{$ruleset_key};
    my ($head, $rs1, $rs2) = split /$;/, $table_key;
    if (defined $rs1) {
        if (defined $rs2) {
            $states{$head}{$rs1}{$rs2} = $ruleset_nr;
        } else {
            $states{$head}{$rs1} = $ruleset_nr;
        }
    } else {
        $states{$head} = $ruleset_nr;
    }
}


## right, now for a testrun - can we actually tile a tree with this thing
my ($tree, $rest) = sexpr->parse('(add (load (const)) (const))');
sub tile {
    my $tree = shift;
    my ($head, $c1, $c2) = @$tree;
    my ($ruleset_nr, $optimum);
    if (defined $c2) {
        my $l1 = tile($c1);
        my $l2 = tile($c2);
        $ruleset_nr = $states{$head}{$l1}{$l2};
        $optimum    = $table{$head}{$l1}{$l2};
    } elsif (defined $c1) {
        my $l1 = tile($c1);
        $ruleset_nr = $states{$head}{$l1};
        $optimum    = $table{$head}{$l1};
    } else {
        $ruleset_nr = $states{$head};
        $optimum    = $table{$head};
    }
    print "Tiled $head to ", sexpr::encode($optimum),sexpr::encode($rules[$optimum->[0]][0]), "\n";
    return $ruleset_nr;
}
tile $tree;
($tree, $rest) = sexpr->parse('(add (const) (load (addr (stack))))');
tile $tree;


__DATA__
# Minimal grammar to test tiler table generator
(tile: (stack) reg 1)
(tile: (addr reg) mem 1)
(tile: (addr reg) reg 2)
(tile: (const) reg 2)
(tile: (load reg) reg 5)
(tile: (load mem) reg 5)
(tile: (add reg reg) reg 2)
(tile: (add reg (const)) reg 3)
(tile: (add reg (load reg)) reg 6)
(tile: (add reg (load mem)) reg 6)
(tile: (sub reg reg) reg 2)
(tile: (sub reg (const)) reg 3)
(tile: (sub reg (load reg)) reg 6)
(tile: (sub reg (load mem)) reg 6)
(tile: (and reg reg) reg 2)
(tile: (and reg (const)) reg 3)
(tile: (and reg (load reg)) reg 6)
(tile: (and reg (load mem)) reg 6)
(tile: (nz reg) flag 2)
(tile: (nz (load mem)) flag 6)
(tile: (all flag) flag 2)
(tile: (if flag reg) reg 2)
(tile: (if (all flag) reg) reg 3)
(tile: (if reg reg) reg 4)
