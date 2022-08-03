#include "src/he_expr.h"
int exprSrcCount(Walker *pWalker, Expr *pExpr) {
  if (pExpr->op == TK_COLUMN || NEVER(pExpr->op == TK_AGG_COLUMN)) {
    int i;
    struct SrcCount *p = pWalker->u.pSrcCount;
    SrcList *pSrc = p->pSrc;
    for (i = 0; i < pSrc->nSrc; i++) {
    }
  }
}
int sqlite3WalkExpr(Walker *pWalker, Expr *pExpr) {
  int rc;
  if (pExpr == 0)
    return WRC_Continue;
  rc = pWalker->xExprCallback(pWalker, pExpr);
  if (rc == WRC_Continue && !ExprHasProperty(pExpr, EP_TokenOnly)) {
    if (sqlite3WalkExpr(pWalker, pExpr->pRight))
      return WRC_Abort;
    if (ExprHasProperty(pExpr, EP_xIsSelect)) {
      if (sqlite3WalkSelect(pWalker, pExpr->x.pSelect))
        return WRC_Abort;
    }
  }
}
int sqlite3WalkExprList(Walker *pWalker, ExprList *p) {
  int i;
  struct ExprList_item *pItem;
  if (p) {
    for (i = p->nExpr, pItem = p->a; i > 0; i--, pItem++) {
      if (sqlite3WalkExpr(pWalker, pItem->pExpr))
        return WRC_Abort;
    }
  }
}
int sqlite3FunctionUsesThisSrc(Expr *pExpr, SrcList *pSrcList) {
  Walker w;
  struct SrcCount cnt;
  w.xExprCallback = exprSrcCount;
  w.u.pSrcCount = &cnt;
  sqlite3WalkExprList(&w, pExpr->x.pList);
}
#include "src/he_resolve.h"
int resolveExprStep(Walker *pWalker, Expr *pExpr) {
  NameContext *pNC;
  Parse *pParse;
  pNC = pWalker->u.pNC;
  pParse = pNC->pParse;
  switch (pExpr->op) {
  case TK_ROW: {
    SrcList *pSrcList = pNC->pSrcList;
    struct SrcList_item *pItem;
  }
  case TK_ID: {
    return lookupName(pParse, 0, 0, pExpr->u.zToken, pNC, pExpr);
    const char *zColumn;
    const char *zTable;
  }
  case TK_FUNCTION: {
    ExprList *pList = pExpr->x.pList;
    int n = pList ? pList->nExpr : 0;
    int no_such_func = 0;
    int wrong_num_args = 0;
    int is_agg = 0;
    int auth;
    const char *zId;
    FuncDef *pDef;
    if (pDef == 0)
      ;
    else {
      is_agg = pDef->xFunc == 0;
    }
    sqlite3WalkExprList(pWalker, pList);
    if (is_agg) {
      NameContext *pNC2 = pNC;
      while (pNC2 && !sqlite3FunctionUsesThisSrc(pExpr, pNC2->pSrcList))
        ;
    }
  }
  case TK_SELECT:
  case TK_IN: {
    if (ExprHasProperty(pExpr, EP_xIsSelect)) {
      sqlite3WalkSelect(pWalker, pExpr->x.pSelect);
    }
  }
  }
  return WRC_Continue;
}
int lookupName(Parse *pParse, const char *zDb, const char *zTab,
               const char *zCol, NameContext *pNC, Expr *pExpr) {
  int cnt = 0;
  int isTrigger = 0;
  if (zDb)
    ;
  pExpr->op = (isTrigger ? TK_TRIGGER : TK_COLUMN);
  if (cnt == 1)
    ;
}
int sqlite3ResolveExprNames(NameContext *pNC, Expr *pExpr) {
  Walker w;
  w.xExprCallback = resolveExprStep;
  w.xSelectCallback = resolveSelectStep;
  w.pParse = pNC->pParse;
  w.u.pNC = pNC;
  sqlite3WalkExpr(&w, pExpr);
}
int resolveSelectStep(Walker *pWalker, Select *p) {
  NameContext *pOuterNC;
  NameContext sNC;
  int isCompound;
  Parse *pParse;
  ExprList *pEList;
  int i;
  ExprList *pGroupBy;
  sqlite3 *db;
  pParse = pWalker->pParse;
  if ((p->selFlags & SF_Expanded) == 0) {
    sqlite3SelectPrep(pParse, p, pOuterNC);
    return (pParse->nErr || db->mallocFailed) ? WRC_Abort : WRC_Prune;
  }
  while (p) {
    sNC.pParse = pParse;
    if (sqlite3ResolveExprNames(&sNC, p->pLimit) ||
        sqlite3ResolveExprNames(&sNC, p->pOffset))
      ;
    pEList = p->pEList;
    for (i = 0; i < pEList->nExpr; i++) {
      Expr *pX = pEList->a[i].pExpr;
      if (sqlite3ResolveExprNames(&sNC, pX))
        ;
    }
  }
}
int sqlite3WalkSelect(Walker *pWalker, Select *p) {
  int rc;
  if (p == 0 ||
      (pWalker->xSelectCallback == 0 && pWalker->xSelectCallback2 == 0))
    ;
  while (p) {
    if (pWalker->xSelectCallback) {
      rc = pWalker->xSelectCallback(pWalker, p);
    }
    p = p->pPrior;
  }
}

#include "src/he_select.h"
void sqlite3SelectPrep(Parse *pParse, Select *p, NameContext *pOuterNC) {
  sqlite3SelectExpand(pParse, p);
  sqlite3SelectAddTypeInfo(pParse, p);
}

int resolveAttachExpr(NameContext *pName, Expr *pExpr) {
  int rc = SQLITE_OK;
  if (pExpr) {
    if (pExpr->op != TK_ID) {
      rc = sqlite3ResolveExprNames(pName, pExpr);
    }
  }
}
void codeAttach(Parse *pParse, int type, FuncDef const *pFunc, Expr *pAuthArg,
                Expr *pFilename, Expr *pDbname, Expr *pKey) {
  int rc;
  NameContext sName;
  memset(&sName, 0, sizeof(NameContext));
  sName.pParse = pParse;
  if (SQLITE_OK != (rc = resolveAttachExpr(&sName, pFilename)) ||
      SQLITE_OK != (rc = resolveAttachExpr(&sName, pKey)))
    ;
}
#include "src/he_attach.h"
void sqlite3Detach(Parse *pParse, Expr *pDbname) {
  static const FuncDef detach_func;
  codeAttach(pParse, SQLITE_DETACH, &detach_func, pDbname, 0, 0, pDbname);
}

int sqlite3RunParser(Parse *pParse, const char *zSql, char **pzErrMsg) {
  int i;
  void *pEngine;
  int tokenType;
  sqlite3 *db = pParse->db;
  i = 0;
  pEngine = sqlite3ParserAlloc((void *(*)(size_t))sqlite3Malloc);
  while (!db->mallocFailed && zSql[i] != 0) {
    pParse->sLastToken.z = &zSql[i];
    pParse->sLastToken.n =
        sqlite3GetToken((unsigned char *)&zSql[i], &tokenType);
    i += pParse->sLastToken.n;
    switch (tokenType) {
    case TK_SPACE:;
    default: {
      sqlite3Parser(pEngine, tokenType, pParse->sLastToken, pParse);
    }
    }
  }
}
int sqlite3Prepare(sqlite3 *db, const char *zSql, int nBytes, int saveSqlFlag,
                   Vdbe *pReprepare, sqlite3_stmt **ppStmt,
                   const char **pzTail) {
  Parse *pParse;
  char *zErrMsg = 0;
  pParse = sqlite3StackAllocZero(db, sizeof(*pParse));
  pParse->db = db;
  if (nBytes >= 0 && (nBytes == 0 || zSql[nBytes - 1] != 0))
    ;
  else {
    sqlite3RunParser(pParse, zSql, &zErrMsg);
  }
}
#include "src/he_btree.h"

int sqlite3LockAndPrepare(sqlite3 *db, const char *zSql, int nBytes,
                          int saveSqlFlag, Vdbe *pOld, sqlite3_stmt **ppStmt,
                          const char **pzTail) {
  int rc;
  rc = sqlite3Prepare(db, zSql, nBytes, saveSqlFlag, pOld, ppStmt, pzTail);
  if (rc == SQLITE_SCHEMA)
    ;
}
int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nBytes,
                       sqlite3_stmt **ppStmt, const char **pzTail) {
  int rc;
  rc = sqlite3LockAndPrepare(db, zSql, nBytes, 1, 0, ppStmt, pzTail);
}
#include "src/he_shell.h"
int main(int argc, char **argv) {
  struct callback_data data;
  const char *zInitFile = 0;
  int i;
  int rc = 0;
  main_init(&data);
  for (i = 1; i < argc; i++) {
    char *z;
    z = argv[i];
    if (z[0] != '-')
      ;
    if (z[1] == '-')
      z++;
    if (strcmp(z, "-separator") == 0 || strcmp(z, "-nullvalue") == 0 ||
        strcmp(z, "-cmd") == 0)
      ;
    else if (strcmp(z, "-init") == 0) {
      zInitFile = cmdline_option_value(argc, argv, ++i);
    }
  }
  rc = process_sqliterc(&data, zInitFile);
  if (rc > 0)
    ;
}
