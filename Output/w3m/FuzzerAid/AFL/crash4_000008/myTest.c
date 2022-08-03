#include "he_file.h"
void HTMLlineproc0(char *line, struct html_feed_environ *h_env, int internal) {
  struct readbuffer *obuf = h_env->obuf;
  struct table_mode *tbl_mode = NULL;
  while (*line != '\0') {
    int pre_mode = (obuf->table_level >= 0) ? tbl_mode->pre_mode : obuf->flag;
  }
}
void loadHTMLstream(URLFile *f, Buffer *newBuf, FILE *src, int internal) {
  Str lineBuf2 = Strnew;
  struct html_feed_environ htmlenv1;
  while ((lineBuf2 = StrmyUFgets(f))->length) {
    HTMLlineproc0(lineBuf2->ptr, &htmlenv1, internal);
  }
}
Buffer *loadHTMLBuffer(URLFile *f, Buffer *newBuf) {
  FILE *src = NULL;
  loadHTMLstream(f, newBuf, src, newBuf->bufferprop & BP_FRAME);
}
Buffer *loadSomething(URLFile *f, Buffer *(*loadproc)(URLFile *, Buffer *),
                      Buffer *defaultbuf) {
  Buffer *buf;
  if (buf = loadproc(f, defaultbuf) == NULL)
    return buf;
}
Buffer *loadGeneralFile(char *path, ParsedURL *volatile current, char *referer,
                        int flag, FormList *volatile request) {
  URLFile f, *volatile of = NULL;
  ParsedURL pu;
  Buffer *b = NULL;
  Buffer *(*volatile proc)(URLFile *, Buffer *) = loadBuffer;
  char *volatile tpath;
  Buffer *volatile t_buf = NULL;
  TextList *extra_header = newTextList();
  unsigned char status = HTST_NORMAL;
  URLOption url_option;
  HRequest hr;
  tpath = path;
  f = openURL(tpath, &pu, current, &url_option, request, extra_header, of, &hr,
              &status);
  proc = loadHTMLBuffer;
  t_buf = newBuffer(INIT_BUFFER_WIDTH);
  if (proc == DO_EXTERNAL)
    ;
  else {
    b = loadSomething(&f, proc, t_buf);
  }
}
int main(int argc, char **argv, char **envp) {
  Buffer *newbuf = NULL;
  int i;
  char **load_argv;
  FormList *request;
  int load_argc = 0;
  for (i = 1; i < argc; i++) {
    if (*argv[i] == '-')
      ;
    else {
      load_argv[load_argc++] = argv[i];
    }
  }
  if (w3m_dump)
    ;
  else {
    i = 0;
    if (i >= 0) {
      char *url;
      url = load_argv[i];
      if (getURLScheme(&url) == SCM_MISSING && !ArgvIsURL)
        ;
      else {
        newbuf = loadGeneralFile(url, NULL, NO_REFERER, 0, request);
      }
    } else if (newbuf == NO_BUFFER)
      if (newbuf->pagerSource ||
          newbuf->currentURL.file && strcmp(newbuf->currentURL.file, "-"))
        ;
  }
}
