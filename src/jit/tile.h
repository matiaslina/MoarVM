struct MVMJitTile {
    void (*emit)(MVMThreadContext *tc, MVMJitCompiler *compiler, MVMJitExprTree *tree,
                 MVMint32 node, MVMJitExprValue **values, MVMJitExprNode *args);
    const MVMint8 *path;
    const char    *expr;
    MVMint32  left_sym;
    MVMint32 right_sym;

    MVMint32  nvals;
    MVMint32  regs;
    MVMJitExprVtype vtype;
};

void MVM_jit_tile_expr_tree(MVMThreadContext *tc, MVMJitExprTree *tree);
void MVM_jit_tile_get_values(MVMThreadContext *tc, MVMJitExprTree *tree, MVMint32 node,
                             const MVMint8 *path, MVMint32 regs,
                             MVMJitExprValue **values, MVMJitExprNode *args);
