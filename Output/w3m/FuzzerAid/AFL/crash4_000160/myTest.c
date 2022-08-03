#include "he_file.h"
void HTMLlineproc0(char *line, struct html_feed_environ *h_env, int internal) {
  struct readbuffer *obuf = h_env->obuf;
  struct table_mode *tbl_mode = NULL;
  if (obuf->table_level >= 0) {
    int pre_mode = (obuf->table_level >= 0) ? tbl_mode->pre_mode : obuf->flag;
  }
}
void loadHTMLstream(URLFile *f, Buffer *newBuf, FILE *src, int internal) {
  Str lineBuf2 = Strnew();
  struct html_feed_environ htmlenv1;
  struct readbuffer obuf;
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
    buf->type = "text/html";
}
Buffer *loadGeneralFile(char *path, ParsedURL *volatile current, char *referer,
                        int flag, FormList *volatile request) {
  URLFile f, *volatile of = NULL;
  ParsedURL pu;
  Buffer *b = NULL;
  Buffer *(*volatile proc)(URLFile *, Buffer *) = loadBuffer;
  char *volatile tpath;
  char *volatile t = "text/plain", *p, *volatile real_type = NULL;
  Buffer *volatile t_buf = NULL;
  TextList *extra_header = newTextList();
  unsigned char status = HTST_NORMAL;
  URLOption url_option;
  HRequest hr;
  tpath = path;
  f = openURL(tpath, &pu, current, &url_option, request, extra_header, of, &hr,
              &status);
  if (f.stream == NULL)
    ;
  else {
  };
  proc = loadHTMLBuffer;
  t_buf = newBuffer(INIT_BUFFER_WIDTH);
  if (flag & RG_FRAME)
    ;
  else {
    b = loadSomething(&f, proc, t_buf);
  }
}
int main(int argc, char **argv, char **envp) {
  Buffer *newbuf = NULL;
  char *p, c;
  int i;
  InputStream redin;
  char **load_argv;
  FormList *request;
  int load_argc = 0;
  load_argv = New_N(char *, argc - 1);
  for (i = 1; i < argc; i++) {
    if (*argv[i] == '-')
      ;
    else {
      load_argv[load_argc++] = argv[i];
    }
  }
  if (load_argc == 0)
    ;
  else {
    i = 0;
  }
  for (; i < load_argc; i++) {
    if (i >= 0) {
      char *url;
      url = load_argv[i];
      if (getURLScheme(&url) == SCM_MISSING && !ArgvIsURL)
        url = file_to_url(load_argv[i]);
      else {
        newbuf = loadGeneralFile(url, NULL, NO_REFERER, 0, request);
      }
      if (newbuf == NULL) {
      } else if (newbuf == NO_BUFFER)
        ;
    } else if (newbuf == NO_BUFFER)
      continue;
  }
}
