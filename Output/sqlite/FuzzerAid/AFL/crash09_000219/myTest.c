#include "src/he_expr.h"
int sqlite3ExprIsInteger(Expr *p, int *pValue) {
  if (p->flags & EP_IntValue) {
  }
  switch (p->op) {
  case TK_UPLUS:;
  case TK_UMINUS: {
    int v;
    if (sqlite3ExprIsInteger(p->pLeft, &v))
      ;
  } break;
  }
}
int exprAlwaysFalse(Expr *p) {
  int v = 0;
  if (!sqlite3ExprIsInteger(p, &v))
    return 0;
}
Expr *sqlite3ExprAnd(sqlite3 *db, Expr *pLeft, Expr *pRight) {
  if (pLeft == 0)
    ;
  else if (exprAlwaysFalse(pLeft) || exprAlwaysFalse(pRight))
    ;
}
Expr *sqlite3PExpr(Parse *pParse, int op, Expr *pLeft, Expr *pRight,
                   const Token *pToken) {
  Expr *p;
  if (op == TK_AND && pLeft && pRight) {
    p = sqlite3ExprAnd(pParse->db, pLeft, pRight);
  } else {
    p = sqlite3ExprAlloc(pParse->db, op, pToken, 1);
  }
  return p;
}
#include "src/he_status.h"

void sqlite3ErrorMsg(Parse *pParse, const char *zFormat, ...) {
  sqlite3 *db = pParse->db;
  if (db)
    ;
}
#include "src/he_printf.h"
char *sqlite3VMPrintf(sqlite3 *db, const char *zFormat, va_list ap) {
  char zBase[SQLITE_PRINT_BUF_SIZE];
}
int sqlite3RunParser(Parse *pParse, const char *zSql, char **pzErrMsg) {
  int i;
  void *pEngine;
  int tokenType;
  sqlite3 *db = pParse->db;
  i = 0;
  pEngine = sqlite3ParserAlloc((void *(*)(size_t))sqlite3Malloc);
  if (pEngine == 0)
    ;
  while (!db->mallocFailed && zSql[i] != 0) {
    pParse->sLastToken.z = &zSql[i];
    pParse->sLastToken.n =
        sqlite3GetToken((unsigned char *)&zSql[i], &tokenType);
    i += pParse->sLastToken.n;
    switch (tokenType) {
    case TK_SPACE:;
    default: {
      sqlite3Parser(pEngine, tokenType, pParse->sLastToken, pParse);
      if (pParse->rc != SQLITE_OK)
        ;
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
  case '-': {
    if (z[1] == '-')
      ;
    *tokenType = TK_MINUS;
    return 1;
  }
  case '(': {
    *tokenType = TK_LP;
    if ((c = z[1]) == '=')
      ;
  }
  case ',': {
    return 1;
  }
  case '\'':
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
    if (c == '\'') {
      return i + 1;
    }
  }
  case '1':
  case '9': {
    *tokenType = TK_INTEGER;
    for (i = 0; sqlite3Isdigit(z[i]); i++)
      ;
  }
  case '?': {
    return i;
    for (i = 1; (c = z[i]) != 0; i++)
      ;
  }
  default: {
    for (i = 1; IdChar(z[i]); i++)
      ;
    *tokenType = keywordCode((char *)z, i);
    return i;
  }
  }
}

#include "src/he_btmutex.h"

int sqlite3VdbeFinalize(Vdbe *p) {
  if (p->magic == VDBE_MAGIC_RUN || p->magic == VDBE_MAGIC_HALT)
    ;
}
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
    else if (strcmp(z, "-init") == 0) {
      zInitFile = cmdline_option_value(argc, argv, ++i);
    }
  }
  rc = process_sqliterc(&data, zInitFile);
  for (i = 1; i < argc; i++)
    ;
}
