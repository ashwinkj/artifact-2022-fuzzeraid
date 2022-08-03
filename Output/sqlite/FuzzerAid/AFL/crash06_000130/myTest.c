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
  rc = pWalker->xExprCallback(pWalker, pExpr);
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
  switch (pExpr->op) {
  case TK_ID: {
    return lookupName(pParse, 0, 0, pExpr->u.zToken, pNC, pExpr);
    Expr *pRight;
  }
  case TK_FUNCTION: {
    ExprList *pList = pExpr->x.pList;
    int n = pList ? pList->nExpr : 0;
    int is_agg = 0;
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
}
int lookupName(Parse *pParse, const char *zDb, const char *zTab,
               const char *zCol, NameContext *pNC, Expr *pExpr) {
  int cnt = 0;
  int cntTab = 0;
  struct SrcList_item *pMatch = 0;
  int isTrigger = 0;
  while (pNC && cnt == 0) {
    if (cnt == 0 && cntTab == 1 && pMatch && sqlite3IsRowid(zCol) &&
        HasRowid(pMatch->pTab))
      ;
    if (cnt == 0) {
      pNC = pNC->pNext;
    }
  }
  pExpr->op = (TK_COLUMN);
}
int sqlite3ResolveExprNames(NameContext *pNC, Expr *pExpr) {
  Walker w;
  if (pExpr == 0)
    return 0;
  w.xExprCallback = resolveExprStep;
  w.xSelectCallback = resolveSelectStep;
  w.pParse = pNC->pParse;
  w.u.pNC = pNC;
  sqlite3WalkExpr(&w, pExpr);
}
int resolveSelectStep(Walker *pWalker, Select *p) {
  NameContext sNC;
  int isCompound;
  Parse *pParse;
  ExprList *pEList;
  int i;
  ExprList *pGroupBy;
  while (p) {
    if (sqlite3ResolveExprNames(&sNC, p->pLimit) ||
        sqlite3ResolveExprNames(&sNC, p->pOffset))
      ;
    pEList = p->pEList;
    for (i = 0; i < pEList->nExpr; i++) {
      Expr *pX = pEList->a[i].pExpr;
      if (sqlite3ResolveExprNames(&sNC, pX))
        ;
      struct ExprList_item *pItem;
    }
  }
}
int sqlite3WalkSelect(Walker *pWalker, Select *p) {
  int rc;
  while (p) {
    if (pWalker->xSelectCallback) {
      rc = pWalker->xSelectCallback(pWalker, p);
    }
    if (sqlite3WalkSelectExpr(pWalker, p) || sqlite3WalkSelectFrom(pWalker, p))
      ;
  }
}
int resolveAttachExpr(NameContext *pName, Expr *pExpr) {
  int rc = SQLITE_OK;
  if (pExpr) {
    if (pExpr->op != TK_ID) {
      rc = sqlite3ResolveExprNames(pName, pExpr);
    }
  }
  return rc;
}
void codeAttach(Parse *pParse, int type, FuncDef const *pFunc, Expr *pAuthArg,
                Expr *pFilename, Expr *pDbname, Expr *pKey) {
  int rc;
  NameContext sName;
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
    default: {
      sqlite3Parser(pEngine, tokenType, pParse->sLastToken, pParse);
    }
    }
  }
}
#include "src/he_tokenize.h"
int sqlite3GetToken(const unsigned char *z, int *tokenType) {
  int i, c;
  switch (*z) {
  case '(': {
    *tokenType = TK_LP;
    return 1;
  }
  case ')': {
    *tokenType = TK_RP;
    return 1;
  }
  default: {
    for (i = 1; IdChar(z[i]); i++)
      ;
    *tokenType = keywordCode((char *)z, i);
    return i;
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
int sqlite3LockAndPrepare(sqlite3 *db, const char *zSql, int nBytes,
                          int saveSqlFlag, Vdbe *pOld, sqlite3_stmt **ppStmt,
                          const char **pzTail) {
  int rc;
  rc = sqlite3Prepare(db, zSql, nBytes, saveSqlFlag, pOld, ppStmt, pzTail);
}
int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nBytes,
                       sqlite3_stmt **ppStmt, const char **pzTail) {
  int rc;
  rc = sqlite3LockAndPrepare(db, zSql, nBytes, 1, 0, ppStmt, pzTail);
  u32 magic;
  if (magic != SQLITE_MAGIC_SICK && magic != SQLITE_MAGIC_OPEN &&
      magic != SQLITE_MAGIC_BUSY)
    ;
}
#include "src/he_shell.h"
int main(int argc, char **argv) {
  struct callback_data data;
  const char *zInitFile = 0;
  int i;
  int rc = 0;
  int warnInmemoryDb = 0;
  main_init(&data);
  for (i = 1; i < argc; i++) {
    char *z;
    z = argv[i];
    if (z[0] != '-')
      ;
    else if (strcmp(z, "-init") == 0) {
      zInitFile = cmdline_option_value(argc, argv, ++i);
    }
  }
  rc = process_sqliterc(&data, zInitFile);
  if (rc > 0)
    ;
}
