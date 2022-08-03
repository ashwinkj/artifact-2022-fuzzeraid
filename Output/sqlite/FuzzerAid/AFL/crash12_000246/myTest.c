#include "src/he_expr.h"
void sqlite3ExprDelete(sqlite3 *db, Expr *p) {
  if (!ExprHasProperty(p, EP_TokenOnly)) {
  }
}
void resolveAlias(Parse *pParse, ExprList *pEList, int iCol, Expr *pExpr,
                  const char *zType, int nSubquery) {
  sqlite3 *db;
  sqlite3ExprDelete(db, pExpr);
}
Expr *sqlite3ExprAddCollateToken(Parse *pParse, Expr *pExpr,
                                 const Token *pCollName) {
  if (pCollName->n > 0)
    ;
}
Expr *sqlite3ExprAlloc(sqlite3 *db, int op, const Token *pToken, int dequote) {
  Expr *pNew;
  int nExtra = 0;
  if (pToken)
    ;
  pNew = sqlite3DbMallocZero(db, sizeof(Expr) + nExtra);
  if (pNew)
    ;
  return pNew;
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
    if (zType[0] != 'G') {
      pItem->u.x.iOrderByCol = (u16)iCol;
    }
  }
  return sqlite3ResolveOrderGroupBy(pParse, pSelect, pOrderBy, zType);
}

int resolveSelectStep(Walker *pWalker, Select *p) {
  NameContext sNC;
  int isCompound;
  while (p) {
    if (!isCompound && resolveOrderGroupBy(&sNC, p, p->pOrderBy, "ORDER"))
      ;
  }
}

void sqlite3ResolveSelectNames(Parse *pParse, Select *p,
                               NameContext *pOuterNC) {
  Walker w;
  w.xSelectCallback = resolveSelectStep;
  sqlite3WalkSelect(&w, p);
}
int sqlite3WalkSelect(Walker *pWalker, Select *p) {
  int rc;
  while (p) {
    if (pWalker->xSelectCallback) {
      rc = pWalker->xSelectCallback(pWalker, p);
    }
  }
  int i;
  ExprList *pOrderBy;
  sqlite3 *db;
  if (pOrderBy->nExpr > db->aLimit[SQLITE_LIMIT_COLUMN]) {
    struct ExprList_item *pItem;
    for (i = 0, pItem = pOrderBy->a; i < pOrderBy->nExpr; i++, pItem++)
      ;
  }
}
void sqlite3SelectPrep(Parse *pParse, Select *p, NameContext *pOuterNC) {
  sqlite3ResolveSelectNames(pParse, p, pOuterNC);
}

int sqlite3Select(Parse *pParse, Select *p, SelectDest *pDest) {
  sqlite3SelectPrep(pParse, p, 0);
}
int sqlite3RunParser(Parse *pParse, const char *zSql, char **pzErrMsg) {
  int i;
  void *pEngine;
  int tokenType;
  sqlite3 *db = pParse->db;
  i = 0;
  pEngine = sqlite3ParserAlloc((void *(*)(size_t))sqlite3Malloc);
  while (!db->mallocFailed && zSql[i] != 0) {
    pParse->sLastToken.n =
        sqlite3GetToken((unsigned char *)&zSql[i], &tokenType);
    i += pParse->sLastToken.n;
    switch (tokenType) {
    case TK_SPACE: {
      break;
    }
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
  int i;
  pParse = sqlite3StackAllocZero(db, sizeof(*pParse));
  for (i = 0; i < db->nDb; i++)
    ;
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
}

#include "src/he_shell.h"
int main(int argc, char **argv) {
  struct callback_data data;
  const char *zInitFile = 0;
  char *zFirstCmd = 0;
  int i;
  int rc = 0;
  int warnInmemoryDb = 0;
  main_init(&data);
  for (i = 1; i < argc; i++) {
    char *z;
    z = argv[i];
    if (strcmp(z, "-separator") == 0 || strcmp(z, "-nullvalue") == 0 ||
        strcmp(z, "-cmd") == 0)
      ;
    else if (strcmp(z, "-init") == 0) {
      zInitFile = cmdline_option_value(argc, argv, ++i);
    }
  }
  rc = process_sqliterc(&data, zInitFile);
  for (i = 1; i < argc; i++)
    ;
}
