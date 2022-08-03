#include "src/he_expr.h"
void sqlite3ExprDelete(sqlite3 *db, Expr *p) {
  if (!ExprHasProperty(p, EP_TokenOnly)) {
    sqlite3ExprDelete(db, p->pLeft);
  }
}
void resolveAlias(Parse *pParse, ExprList *pEList, int iCol, Expr *pExpr,
                  const char *zType, int nSubquery) {
  sqlite3 *db;
  sqlite3ExprDelete(db, pExpr);
}

int sqlite3ResolveOrderGroupBy(Parse *pParse, Select *pSelect,
                               ExprList *pOrderBy, const char *zType) {
  int i;
  ExprList *pEList;
  struct ExprList_item *pItem;
  for (i = 0, pItem = pOrderBy->a; i < pOrderBy->nExpr; i++, pItem++) {
    if (pItem->u.x.iOrderByCol) {
      resolveAlias(pParse, pEList, pItem->u.x.iOrderByCol - 1, pItem->pExpr,
                   zType, 0);
    }
  }
}
int resolveOrderGroupBy(NameContext *pNC, Select *pSelect, ExprList *pOrderBy,
                        const char *zType) {
  int i, j;
  int iCol;
  struct ExprList_item *pItem;
  Parse *pParse;
  for (i = 0, pItem = pOrderBy->a; i < pOrderBy->nExpr; i++, pItem++) {
    Expr *pE = pItem->pExpr;
    Expr *pE2 = sqlite3ExprSkipCollate(pE);
    if (zType[0] != 'G')
      ;
    if (sqlite3ExprIsInteger(pE2, &iCol)) {
      pItem->u.x.iOrderByCol = (u16)iCol;
    }
  }
  return sqlite3ResolveOrderGroupBy(pParse, pSelect, pOrderBy, zType);
}
int sqlite3ExprIsInteger(Expr *p, int *pValue) {
}
int resolveSelectStep(Walker *pWalker, Select *p) {
  NameContext sNC;
  ExprList *pGroupBy;
  sqlite3 *db;
  while (p) {
    if (sqlite3ResolveExprNames(&sNC, p->pLimit) ||
        sqlite3ResolveExprNames(&sNC, p->pOffset))
      ;
    pGroupBy = p->pGroupBy;
    if (pGroupBy || (sNC.ncFlags & NC_HasAgg) != 0) {
      if (resolveOrderGroupBy(&sNC, p, pGroupBy, "GROUP") || db->mallocFailed)
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
void sqlite3ResolveSelectNames(Parse *pParse, Select *p,
                               NameContext *pOuterNC) {
  Walker w;
  w.xSelectCallback = resolveSelectStep;
  sqlite3WalkSelect(&w, p);
}
#include "src/he_select.h"
void sqlite3SelectPrep(Parse *pParse, Select *p, NameContext *pOuterNC) {
  sqlite3ResolveSelectNames(pParse, p, pOuterNC);
}
int sqlite3Select(Parse *pParse, Select *p, SelectDest *pDest) {
  int i, j;
  WhereInfo *pWInfo;
  Vdbe *v;
  SrcList *pTabList;
  ExprList *pGroupBy;
  DistinctCtx sDistinct;
  AggInfo sAggInfo;
  sqlite3SelectPrep(pParse, p, 0);
  for (i = 0; !p->pPrior && i < pTabList->nSrc; i++)
    ;
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
    for (i = 1; sqlite3Isspace(z[i]); i++)
      ;
    return i;
  }
  case '(': {
    *tokenType = TK_LP;
    return 1;
  }
  case ')': {
    *tokenType = TK_RP;
    for (i = 1; (c = z[i]) != 0; i++) {
      return i + 1;
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
  main_init(&data);
  for (i = 1; i < argc; i++) {
    char *z;
    z = argv[i];
    if (strcmp(z, "-separator") == 0 || strcmp(z, "-nullvalue") == 0 ||
        strcmp(z, "-cmd") == 0)
      ;
    else if (strcmp(z, "-init") == 0) {
      zInitFile = cmdline_option_value(argc, argv, ++i);
    } else if (strcmp(z, "-vfs") == 0)
      ;
  }
  rc = process_sqliterc(&data, zInitFile);
  for (i = 1; i < argc; i++)
    ;
}
