#include "src/he_expr.h"
int exprSrcCount(Walker *pWalker, Expr *pExpr) {
  if (pExpr->op == TK_COLUMN || NEVER(pExpr->op == TK_AGG_COLUMN)) {
    int i;
    struct SrcCount *p = pWalker->u.pSrcCount;
    SrcList *pSrc = p->pSrc;
    for (i = 0; i < pSrc->nSrc; i++) {
    }
  }
  return WRC_Continue;
}
int sqlite3WalkExpr(Walker *pWalker, Expr *pExpr) {
  int rc;
  if (pExpr == 0)
    return WRC_Continue;
  rc = pWalker->xExprCallback(pWalker, pExpr);
  if (rc == WRC_Continue && !ExprHasProperty(pExpr, EP_TokenOnly)) {
    if (sqlite3WalkExpr(pWalker, pExpr->pLeft))
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
  cnt.pSrc = pSrcList;
  sqlite3WalkExprList(&w, pExpr->x.pList);
}
#include "src/he_resolve.h"
int resolveExprStep(Walker *pWalker, Expr *pExpr) {
  NameContext *pNC;
  Parse *pParse;
  pNC = pWalker->u.pNC;
  pParse = pNC->pParse;
  switch (pExpr->op) {
  case TK_DOT: {
    const char *zColumn;
    const char *zTable;
    const char *zDb;
    return lookupName(pParse, zDb, zTable, zColumn, pNC, pExpr);
  }
  case TK_FUNCTION: {
    ExprList *pList = pExpr->x.pList;
    int n = pList ? pList->nExpr : 0;
    int is_agg = 0;
    int nId;
    const char *zId;
    FuncDef *pDef;
    u8 enc = ENC(pParse->db);
    zId = pExpr->u.zToken;
    nId = sqlite3Strlen30(zId);
    pDef = sqlite3FindFunction(pParse->db, zId, nId, n, enc, 0);
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
  }
  return WRC_Continue;
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
  NameContext sNC;
  Parse *pParse;
  ExprList *pEList;
  int i;
  pParse = pWalker->pParse;
  while (p) {
    memset(&sNC, 0, sizeof(sNC));
    sNC.pParse = pParse;
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
  }
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
  case ' ':
  case '\r': {
    *tokenType = TK_MINUS;
    return 1;
  }
  case '(': {
    *tokenType = TK_LP;
    return 1;
  }
  case ')': {
    *tokenType = TK_RP;
    return 1;
  }
  case '.': {
    {
      *tokenType = TK_DOT;
      return 1;
    }
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
  int i;
  pParse = sqlite3StackAllocZero(db, sizeof(*pParse));
  for (i = 0; i < db->nDb; i++)
    ;
  pParse->db = db;
  if (nBytes >= 0 && (nBytes == 0 || zSql[nBytes - 1] != 0))
    ;
  else {
    sqlite3RunParser(pParse, zSql, &zErrMsg);
    if (pParse->explain == 2)
      ;
  }
  VTable *p = db->pDisconnect;
  if (p)
    ;
}
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
  int warnInmemoryDb = 0;
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
#ifdef SQLITE_ENABLE_VFSTRACE
#endif
    }
  }
  rc = process_sqliterc(&data, zInitFile);
  for (i = 1; i < argc; i++)
    ;
}
