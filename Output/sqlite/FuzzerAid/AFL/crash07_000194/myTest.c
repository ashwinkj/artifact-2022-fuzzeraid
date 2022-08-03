#include "src/he_resolve.h"
int sqlite3MatchSpanName(const char *zSpan, const char *zCol, const char *zTab,
                         const char *zDb) {
  int n;
  for (n = 0; ALWAYS(zSpan[n]) && zSpan[n] != '.'; n++) {
  }
}
#include "src/he_select.h"
int selectExpander(Walker *pWalker, Select *p) {
  Parse *pParse = pWalker->pParse;
  int i, j, k;
  SrcList *pTabList;
  ExprList *pEList;
  struct SrcList_item *pFrom;
  sqlite3 *db = pParse->db;
  Expr *pE, *pRight, *pExpr;
  pTabList = p->pSrc;
  pEList = p->pEList;
  for (i = 0, pFrom = pTabList->a; i < pTabList->nSrc; i++, pFrom++) {
    Table *pTab;
    if (pFrom->zName == 0) {
      Select *pSel = pFrom->pSelect;
      pFrom->pTab = pTab = sqlite3DbMallocZero(db, sizeof(Table));
      selectColumnsFromExprList(pParse, pSel->pEList, &pTab->nCol, &pTab->aCol);
    }
  }
  if (k < pEList->nExpr) {
    struct ExprList_item *a = pEList->a;
    assert((p->selFlags & SF_NestedFrom) == 0 ||
           ((flags & SQLITE_FullColNames) == 0 &&
            (flags & SQLITE_ShortColNames) != 0));
    for (k = 0; k < pEList->nExpr; k++) {
      pE = a[k].pExpr;
      pRight = pE->pRight;
      if (pE->op != TK_ALL && (pE->op != TK_DOT || pRight->op != TK_ALL))
        ;
      else {
        char *zTName = 0;
        if (pE->op == TK_DOT) {
          zTName = pE->pLeft->u.zToken;
        }
        for (i = 0, pFrom = pTabList->a; i < pTabList->nSrc; i++, pFrom++) {
          Table *pTab = pFrom->pTab;
          Select *pSub = pFrom->pSelect;
          for (j = 0; j < pTab->nCol; j++) {
            char *zName = pTab->aCol[j].zName;
            if (zTName && pSub &&
                sqlite3MatchSpanName(pSub->pEList->a[j].zSpan, 0, zTName, 0) ==
                    0)
              ;
          }
        }
      }
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
#include "src/he_malloc.h"
int sqlite3LockAndPrepare(sqlite3 *db, const char *zSql, int nBytes,
                          int saveSqlFlag, Vdbe *pOld, sqlite3_stmt **ppStmt,
                          const char **pzTail) {
  int rc;
  rc = sqlite3Prepare(db, zSql, nBytes, saveSqlFlag, pOld, ppStmt, pzTail);
}
int sqlite3Prepare(sqlite3 *db, const char *zSql, int nBytes, int saveSqlFlag,
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
    case TK_SPACE: {
      break;
    }
    default: {
      sqlite3Parser(pEngine, tokenType, pParse->sLastToken, pParse);
    }
    }
  }
}

void *sqlite3Malloc(int n);

int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nBytes,
                       sqlite3_stmt **ppStmt, const char **pzTail) {
  int rc;
  rc = sqlite3LockAndPrepare(db, zSql, nBytes, 1, 0, ppStmt, pzTail);
}
int sqlite3Select(Parse *pParse, Select *p, SelectDest *pDest) {
  SortCtx sSort;
  if (IgnorableOrderby(pDest))
    ;
  sqlite3SelectPrep(pParse, p, 0);
  if ((p->selFlags & (SF_Distinct | SF_Aggregate)) == SF_Distinct &&
      sqlite3ExprListCompare(sSort.pOrderBy, p->pEList, -1) == 0)
    ;
}
void sqlite3SelectPrep(Parse *pParse, Select *p, NameContext *pOuterNC) {
  if (NEVER(p == 0))
    return;
  sqlite3SelectExpand(pParse, p);
}

void sqlite3SelectExpand(Parse *pParse, Select *pSelect) {
  Walker w;
  w.pParse = pParse;
  if (pParse->hasCompound)
    ;
  w.xSelectCallback = selectExpander;
  sqlite3WalkSelect(&w, pSelect);
}

#include "src/he_shell.h"
int main(int argc, char **argv) {
  char *zErrMsg = 0;
  struct callback_data data;
  const char *zInitFile = 0;
  char *zFirstCmd = 0;
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
    }
  }
  if (data.zDbFilename == 0)
    ;
  rc = process_sqliterc(&data, zInitFile);
  if (rc > 0)
    ;
  if (zFirstCmd)
    ;
}
