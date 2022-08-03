#include "src/he_util.h"
int sqlite3Dequote(char *z) {
  char quote;
  int i, j;
  for (i = 1, j = 0;; i++) {
    if (z[i] == quote) {
    }
  }
}
Expr *sqlite3ExprAlloc(sqlite3 *db, int op, const Token *pToken, int dequote) {
  Expr *pNew;
  int nExtra = 0, iValue = 0;

  if (pToken) {
    if (op != TK_INTEGER || pToken->z == 0 ||
        sqlite3GetInt32(pToken->z, &iValue) == 0) {
      nExtra = pToken->n + 1;
    }
  }
  pNew = sqlite3DbMallocZero(db, sizeof(Expr) + nExtra);
  if (pNew) {
    if (pToken) {
      if (nExtra == 0)
        ;
      else {
        int c;
        if (dequote && nExtra >= 3 && (c = pToken->z[0]) == '\'' || c == '"' ||
            c == '[' || c == '`') {
          sqlite3Dequote(pNew->u.zToken);
        }
      }
    }
  }
}
Expr *sqlite3ExprAddCollateToken(Parse *pParse, Expr *pExpr,
                                 const Token *pCollName) {
  if (pCollName->n > 0) {
    Expr *pNew = sqlite3ExprAlloc(pParse->db, TK_COLLATE, pCollName, 1);
  }
}
Expr *sqlite3PExpr(Parse *pParse, int op, Expr *pLeft, Expr *pRight,
                   const Token *pToken) {
}
Select *sqlite3SelectNew(Parse *pParse, ExprList *pEList, SrcList *pSrc,
                         Expr *pWhere, ExprList *pGroupBy, Expr *pHaving,
                         ExprList *pOrderBy, u16 selFlags, Expr *pLimit,
                         Expr *pOffset) {
  Select standin;
}
ExprList *sqlite3ExprListAppend(Parse *pParse, ExprList *pList, Expr *pExpr) {
}
int sqlite3RunParser(Parse *pParse, const char *zSql, char **pzErrMsg) {
  int i, tokenType;
  void *pEngine;
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
    case TK_SEMI: {
      pParse->zTail = &zSql[i];
    }
    default: {
      sqlite3Parser(pEngine, tokenType, pParse->sLastToken, pParse);
      if (pParse->rc != SQLITE_OK) {
        goto abort_parse;
      }
    }
    }
  }
abort_parse:;
}
#include "src/he_tokenize.h"
int sqlite3GetToken(const unsigned char *z, int *tokenType) {
  int i, c;
  switch (*z) {
  case ' ':
  case '\r': {
    for (i = 1; sqlite3Isspace(z[i]); i++)
      ;
    *tokenType = TK_SPACE;
    return i;
  }
  case '(':;
  case ')':;
  case ';': {
    *tokenType = TK_SEMI;
    return 1;
  }
  case '"': {
    int delim = z[0];
    for (i = 1; (c = z[i]) != 0; i++) {
      if (c == delim) {
        if (z[i + 1] == delim)
          ;
        else {
          break;
        }
      }
    }
    if (c == '\'')
      ;
    else if (c != 0) {
      *tokenType = TK_ID;
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
  pParse = sqlite3StackAllocZero(db, sizeof *pParse);
  pParse->db = db;
  if (nBytes >= 0 && (nBytes == 0 || zSql[nBytes - 1] != 0))
    ;
  else {
    sqlite3RunParser(pParse, zSql, &zErrMsg);
    *pzTail = pParse->zTail;
  };
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
  int i, rc = 0;
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
}
