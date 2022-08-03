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
      char c = (char)wtf_get_code((wc_uchar *)p) & 0x7f - SYMBOL_BASE;
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
#include "he_main.h"
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
  char line_str = NULL;
  char **load_argv;
  FormList *request;
  int load_argc = 0;
  int load_bookmark = FALSE;
  int visual_start = FALSE;
  int open_new_tab = FALSE;
  char search_header = FALSE;
  char *default_type = NULL;
  char *post_file = NULL;
  Str err_msg;
  char *Locale = NULL;
  wc_uint8 auto_detect;
  CurrentDir = currentdir();
  for (i = 1; i < argc; i++) {
    if (*argv[i] == '-') {
      if (!strcmp("-config", argv[i]))
        ;
    }
    if (*argv[i] == '-') {
      if (!strcmp("-t", argv[i]))
        ;
      else if (!strcmp("-r", argv[i]))
        ShowEffect = FALSE;
      else if (!strcmp("-l", argv[i])) {
        if (argv[i][2] != '\0')
          p = argv[i] + 2;
        if (BookmarkFile[0] != '~' && BookmarkFile[0] != '/') {
          Str tmp = Strnew_charp(CurrentDir);
          COLS = MAXIMUM_COLS;
        }
      } else if (!strcmp("-num", argv[i]))
        displayTitleTerm = argv[i] + 7;
      else if (!strcmp("-o", argv[i]) || !strcmp("-show-option", argv[i])) {
        if (!strcmp("-show-option", argv[i]) || ++i >= argc ||
            !strcmp(argv[i], "?"))
          ;
      }
    } else {
      load_argv[load_argc++] = argv[i];
    }
    w3m_dump = DUMP_BUFFER;
  }
  if (load_argc == 0)
    ;
  else {
    i = 0;
    if (i >= 0) {
      char *url;
      if (getURLScheme(&url) == SCM_MISSING && !ArgvIsURL)
        url = file_to_url(load_argv[i]);
      url = url_encode(conv_from_system(load_argv[i]), NULL, 0);
      if (w3m_dump == DUMP_HEAD)
        ;
      else {
        newbuf = loadGeneralFile(url, NULL, NO_REFERER, 0, request);
      }
    } else if (newbuf == NO_BUFFER)
      if (newbuf->pagerSource ||
          newbuf->real_scheme == SCM_LOCAL && newbuf->header_source &&
              newbuf->currentURL.file && strcmp(newbuf->currentURL.file, "-"))
        newbuf->search_header = search_header;
    if (CurrentTab == NULL) {
      FirstTab = LastTab = CurrentTab = newTab();
      Firstbuf = Currentbuf = newbuf;
    }
    if (w3m_dump)
      do_dump(Currentbuf);
    else {
      if ('0' <= c && c <= '9' && prec_num ||
          GlobalKeymap[c] == FUNCNAME_nulcmd)
        ;
    }
  }
}
