#include "he_Str.h"
void Strcat_charp(Str x, const char *y) {
  Strcat_charp_n(x, y, strlen(y));
}
#include "he_file.h"
Str conv_symbol(Line *l) {
  Str tmp = NULL;
  char *p = l->lineBuf, *ep = p + l->len;
  Lineprop *pr = l->propBuf;
  int w;
  char *symbol = NULL;
  for (; p < ep; p++, pr++) {
    if (*pr & PC_SYMBOL) {
      char c = ((char)wtf_get_code((wc_uchar *)p) & 0x7f) - SYMBOL_BASE;
      if (tmp == NULL) {
        symbol = get_symbol(DisplayCharset, &w);
      }
      Strcat_charp(tmp, symbol[(int)c]);
    } else if (tmp != NULL)
      Strcat_char(tmp, *p);
  }
}
void _saveBuffer(Buffer *buf, Line *l, FILE *f, int cont) {
  Str tmp;
  for (; l != NULL; l = l->next) {
    tmp = conv_symbol(l);
  }
}
void saveBuffer(Buffer *buf, FILE *f, int cont) {
  _saveBuffer(buf, buf->firstLine, f, cont);
}
void do_dump(Buffer *buf) {
  if (w3m_dump == DUMP_BUFFER) {
    saveBuffer(buf, stdout, FALSE);
  }
}
int main(int argc, char **argv, char **envp) {
  Buffer *newbuf = NULL;
  char *p, c;
  int i;
  InputStream redin;
  char *line_str = NULL;
  char **load_argv;
  FormList *request;
  int load_argc = 0;
  i = 1;
  while (i < argc) {
    if (*argv[i] == '-')
      ;
    else {
      load_argv[load_argc++] = argv[i];
    }
    i++;
    w3m_dump = DUMP_BUFFER;
  }
  if (w3m_dump) {
    COLS = DEFAULT_COLS;
    i = 0;
  }
  for (; i < load_argc; i++) {
    if (i >= 0) {
      char *url;
      url = load_argv[i];
      if (getURLScheme(&url) == SCM_MISSING && !ArgvIsURL)
        ;
      else {
        newbuf = loadGeneralFile(url, NULL, NO_REFERER, 0, request);
      }
      if (newbuf == NULL) {
      } else if (newbuf == NO_BUFFER)
        ;
      FirstTab = LastTab = CurrentTab = newTab();
      Firstbuf = Currentbuf = newbuf;
    }
    do_dump(Currentbuf);
  }
}
