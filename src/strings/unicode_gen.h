
#define MVMNUMUNICODEEXTENTS 104


struct MVMUnicodeNamedValue {
    const char *name;
    MVMint32 value;
};
#define num_unicode_property_keypairs 3600

MVMint32 MVM_unicode_is_in_block(MVMThreadContext *tc, MVMString *str, MVMint64 pos, MVMString *block);

#define MVMCODEPOINTNAMESCOUNT 49764
#define MVMNUMPROPERTYCODES 93


#define num_unicode_property_value_keypairs 3181

typedef enum {
    MVM_UNICODE_PROPERTY_DECOMP_SPEC = 1,
    MVM_UNICODE_PROPERTY_CASE_CHANGE_INDEX = 2,
    MVM_UNICODE_PROPERTY_NUMERIC_VALUE_NUMERATOR = 3,
    MVM_UNICODE_PROPERTY_CASE_FOLDING = 4,
    MVM_UNICODE_PROPERTY_BLOCK = 5,
    MVM_UNICODE_PROPERTY_BIDI_MIRRORING_GLYPH = 6,
    MVM_UNICODE_PROPERTY_JOINING_TYPE = 7,
    MVM_UNICODE_PROPERTY_NUMERIC_VALUE = 8,
    MVM_UNICODE_PROPERTY_SCRIPT = 9,
    MVM_UNICODE_PROPERTY_JOINING_GROUP = 10,
    MVM_UNICODE_PROPERTY_CANONICAL_COMBINING_CLASS = 11,
    MVM_UNICODE_PROPERTY_HANGUL_SYLLABLE_TYPE = 12,
    MVM_UNICODE_PROPERTY_AGE = 13,
    MVM_UNICODE_PROPERTY_BIDI_CLASS = 14,
    MVM_UNICODE_PROPERTY_WORD_BREAK = 15,
    MVM_UNICODE_PROPERTY_GENERAL_CATEGORY = 16,
    MVM_UNICODE_PROPERTY_DECOMPOSITION_TYPE = 17,
    MVM_UNICODE_PROPERTY_LINE_BREAK = 18,
    MVM_UNICODE_PROPERTY_NUMERIC_TYPE = 19,
    MVM_UNICODE_PROPERTY_DIGIT = 20,
    MVM_UNICODE_PROPERTY_ASCII_HEX_DIGIT = 21,
    MVM_UNICODE_PROPERTY_NUMERIC_VALUE_DENOMINATOR = 22,
    MVM_UNICODE_PROPERTY_SENTENCE_BREAK = 23,
    MVM_UNICODE_PROPERTY_GRAPHEME_CLUSTER_BREAK = 24,
    MVM_UNICODE_PROPERTY_NFKC_QC = 25,
    MVM_UNICODE_PROPERTY_NFC_QC = 26,
    MVM_UNICODE_PROPERTY_ALPHABETIC = 27,
    MVM_UNICODE_PROPERTY_ANY = 28,
    MVM_UNICODE_PROPERTY_ASSIGNED = 29,
    MVM_UNICODE_PROPERTY_BIDI_CONTROL = 30,
    MVM_UNICODE_PROPERTY_BIDI_MIRRORED = 31,
    MVM_UNICODE_PROPERTY_C = 32,
    MVM_UNICODE_PROPERTY_CASE_FOLDING_SIMPLE = 33,
    MVM_UNICODE_PROPERTY_CASE_IGNORABLE = 34,
    MVM_UNICODE_PROPERTY_CASED = 35,
    MVM_UNICODE_PROPERTY_CHANGES_WHEN_CASEFOLDED = 36,
    MVM_UNICODE_PROPERTY_CHANGES_WHEN_CASEMAPPED = 37,
    MVM_UNICODE_PROPERTY_CHANGES_WHEN_LOWERCASED = 38,
    MVM_UNICODE_PROPERTY_CHANGES_WHEN_NFKC_CASEFOLDED = 39,
    MVM_UNICODE_PROPERTY_CHANGES_WHEN_TITLECASED = 40,
    MVM_UNICODE_PROPERTY_CHANGES_WHEN_UPPERCASED = 41,
    MVM_UNICODE_PROPERTY_DASH = 42,
    MVM_UNICODE_PROPERTY_DEFAULT_IGNORABLE_CODE_POINT = 43,
    MVM_UNICODE_PROPERTY_DEPRECATED = 44,
    MVM_UNICODE_PROPERTY_DIACRITIC = 45,
    MVM_UNICODE_PROPERTY_EXTENDER = 46,
    MVM_UNICODE_PROPERTY_FULL_COMPOSITION_EXCLUSION = 47,
    MVM_UNICODE_PROPERTY_GRAPHEME_BASE = 48,
    MVM_UNICODE_PROPERTY_GRAPHEME_EXTEND = 49,
    MVM_UNICODE_PROPERTY_GRAPHEME_LINK = 50,
    MVM_UNICODE_PROPERTY_HEX_DIGIT = 51,
    MVM_UNICODE_PROPERTY_HYPHEN = 52,
    MVM_UNICODE_PROPERTY_IDS_BINARY_OPERATOR = 53,
    MVM_UNICODE_PROPERTY_IDS_TRINARY_OPERATOR = 54,
    MVM_UNICODE_PROPERTY_ID_CONTINUE = 55,
    MVM_UNICODE_PROPERTY_ID_START = 56,
    MVM_UNICODE_PROPERTY_IDEOGRAPHIC = 57,
    MVM_UNICODE_PROPERTY_JOIN_CONTROL = 58,
    MVM_UNICODE_PROPERTY_L = 59,
    MVM_UNICODE_PROPERTY_LC = 60,
    MVM_UNICODE_PROPERTY_LOGICAL_ORDER_EXCEPTION = 61,
    MVM_UNICODE_PROPERTY_LOWERCASE = 62,
    MVM_UNICODE_PROPERTY_M = 63,
    MVM_UNICODE_PROPERTY_MATH = 64,
    MVM_UNICODE_PROPERTY_N = 65,
    MVM_UNICODE_PROPERTY_NFD_QC = 66,
    MVM_UNICODE_PROPERTY_NFKD_QC = 67,
    MVM_UNICODE_PROPERTY_NONCHARACTER_CODE_POINT = 68,
    MVM_UNICODE_PROPERTY_OTHER_ALPHABETIC = 69,
    MVM_UNICODE_PROPERTY_OTHER_DEFAULT_IGNORABLE_CODE_POINT = 70,
    MVM_UNICODE_PROPERTY_OTHER_GRAPHEME_EXTEND = 71,
    MVM_UNICODE_PROPERTY_OTHER_ID_CONTINUE = 72,
    MVM_UNICODE_PROPERTY_OTHER_ID_START = 73,
    MVM_UNICODE_PROPERTY_OTHER_LOWERCASE = 74,
    MVM_UNICODE_PROPERTY_OTHER_MATH = 75,
    MVM_UNICODE_PROPERTY_OTHER_UPPERCASE = 76,
    MVM_UNICODE_PROPERTY_P = 77,
    MVM_UNICODE_PROPERTY_PATTERN_SYNTAX = 78,
    MVM_UNICODE_PROPERTY_PATTERN_WHITE_SPACE = 79,
    MVM_UNICODE_PROPERTY_QUOTATION_MARK = 80,
    MVM_UNICODE_PROPERTY_RADICAL = 81,
    MVM_UNICODE_PROPERTY_S = 82,
    MVM_UNICODE_PROPERTY_STERM = 83,
    MVM_UNICODE_PROPERTY_SOFT_DOTTED = 84,
    MVM_UNICODE_PROPERTY_TERMINAL_PUNCTUATION = 85,
    MVM_UNICODE_PROPERTY_UNIFIED_IDEOGRAPH = 86,
    MVM_UNICODE_PROPERTY_UPPERCASE = 87,
    MVM_UNICODE_PROPERTY_VARIATION_SELECTOR = 88,
    MVM_UNICODE_PROPERTY_WHITE_SPACE = 89,
    MVM_UNICODE_PROPERTY_XID_CONTINUE = 90,
    MVM_UNICODE_PROPERTY_XID_START = 91,
    MVM_UNICODE_PROPERTY_Z = 92,
} MVM_unicode_property_codes;