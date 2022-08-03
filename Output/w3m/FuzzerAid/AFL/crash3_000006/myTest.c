#include "he_file.h"
void HTMLlineproc2body(Buffer *buf, Str (*feed)(), int llimit) {
  char *outc = NULL;
  Lineprop *outp = NULL;
  int out_size = 0;
  Anchor *a_href = NULL, *a_img = NULL, *a_form = NULL;
  char p, q, *r, s, *t, *str;
  Lineprop mode, effect, ex_effect;
  int pos;
  union frameset_element *idFrame = NULL;
  char id = NULL;
  int hseq, form_id;
  Str line;
  char *endp;
  Anchor **a_select = NULL;
  while ((line = feed()) != NULL) {
    str = line->ptr;
    while (str < endp) {
      if ((effect | ex_efct(ex_effect)) & PC_SYMBOL && *str != '<') {
        PPUSH(mode | effect | ex_efct(ex_effect), *str++);
      } else if (*str == '&')
        ;
      else {
        struct parsed_tag *tag;
        if (!(tag = parse_tag(&str, TRUE)))
          continue;
        switch (tag->tagid) {
        case HTML_INPUT_ALT:;
        case HTML_N_SELECT_INT:
          if (n_select >= 0) {
            FormItemList *item = (FormItemList *)a_select[n_select]->url;
          }
        }
        putAnchor(idFrame->body->nameList, id, NULL, (Anchor **)NULL, NULL,
                  NULL, '\0', currentLn(buf), pos);
      }
    }
  }
}
#include "he_parsetagx.h"
struct parsed_tag *parse_tag(char **s, int internal) {
  struct parsed_tag *tag = NULL;
  int tag_id;
  char tagname[MAX_TAG_LEN], attrnameMAX_TAG_LEN;
  char *p, *q;
  p = tagname;
  if (*q == '/') {
    *p++ = *q++;
  }
  while (*q && !IS_SPACE(*q) && !(tagname[0] != '/' && *q == '/') &&
         *q != '>' && p - tagname < MAX_TAG_LEN - 1) {
    *p++ = TOLOWER(*q);
    q++;
  }
  *p = '\0';
  tag_id = getHash_si(&tagtable, tagname, HTML_UNKNOWN);
  tag = New(struct parsed_tag);
  tag->tagid = tag_id;
  return tag;
}
int getescapechar(char **str) {
  char *p = *str, q;
  if (!IS_ALPHA(*p)) {
    return -1;
  }
}
void HTMLlineproc2(Buffer *buf, TextLineList *tl) {
  _tl_lp2 = tl->first;
  HTMLlineproc2body(buf, textlist_feed, -1);
}
void loadHTMLstream(URLFile *f, Buffer *newBuf, FILE *src, int internal) {
  struct environment envs[MAX_ENV_LEVEL];
  Str lineBuf2 = Strnew;
  wc_ces charset = WC_CES_US_ASCII;
  wc_ces volatile doc_charset = DocumentCharset;
  struct html_feed_environ htmlenv1;
  struct readbuffer obuf;
  init_henv(&htmlenv1, &obuf, envs, MAX_ENV_LEVEL, NULL, newBuf->width, 0);
  htmlenv1.buf = newTextLineList();
  while ((lineBuf2 = StrmyUFgets(f))->length) {
    lineBuf2 = convertLine(f, lineBuf2, HTML_MODE, &charset, doc_charset);
    HTMLlineproc0(lineBuf2->ptr, &htmlenv1, internal);
  }
  HTMLlineproc2(newBuf, htmlenv1.buf);
}
Buffer *loadHTMLBuffer(URLFile *f, Buffer *newBuf) {
  FILE *src = NULL;
  loadHTMLstream(f, newBuf, src, newBuf->bufferprop & BP_FRAME);
}
Buffer *loadSomething(URLFile *f, Buffer *(*loadproc)(URLFile *, Buffer *),
                      Buffer *defaultbuf) {
  Buffer *buf;
  if (buf = loadproc(f, defaultbuf) == NULL)
    buf->type = "text/plain";
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
  if (flag & RG_FRAME) {
  } else {
    b = loadSomething(&f, proc, t_buf);
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
  char *post_file = NULL;
  i = 1;
  while (i < argc) {
    if (*argv[i] == '-') {
    } else {
      load_argv[load_argc++] = argv[i];
    }
    i++;
  }
  if (load_argc == 0)
    ;
  else {
    if (i >= 0) {
      char *url;
      url = load_argv[i];
      if (getURLScheme(&url) == SCM_MISSING && !ArgvIsURL)
        url = file_to_url(load_argv[i]);
      else {
        newbuf = loadGeneralFile(url, NULL, NO_REFERER, 0, request);
      }
    }
  }
}
