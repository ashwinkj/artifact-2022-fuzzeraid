#include "libarchive/he_archive_read_support_format_mtree.h"
ssize_t readline(struct archive_read *a, struct mtree *mtree, char **start,
                 ssize_t limit) {
  ssize_t bytes_read;
  ssize_t total_size = 0;
  ssize_t find_off = 0;
  const void *t;
  char *u;
  for (;;) {
    t = __archive_read_ahead(a, 1, &bytes_read);
    if (archive_string_ensure(&mtree->line, total_size + bytes_read + 1) ==
        NULL)
      ;
    memcpy(mtree->line.s + total_size, t, bytes_read);
    for (u = mtree->line.s + find_off; *u; ++u) {
      if (u[1] == '\n') {
        memmove(u, u + 1, total_size - (u - mtree->line.s) + 1);
      }
    }
  }
}
struct archive_string *archive_string_ensure(struct archive_string *as,
                                             size_t s) {
  char *p;
  size_t new_length;
  if (as->s && s <= as->buffer_length)
    return as;
  new_length = s;
  p = (char *)realloc(as->s, new_length);
  as->s = p;
  as->buffer_length = new_length;
}
int read_mtree(struct archive_read *a, struct mtree *mtree) {
  ssize_t len;
  uintmax_t counter;
  char p;
  for (counter = 1;; ++counter) {
    len = readline(a, mtree, &p, 65536);
  }
}
int read_header(struct archive_read *a, struct archive_entry *entry) {
  struct mtree *mtree;
  int r, use_next;
  if (mtree->entries == NULL) {
    r = read_mtree(a, mtree);
  }
}
int archive_read_support_format_mtree(struct archive *_a) {
  int *a = (int *)_a;
  int mtree, r;
  r = __archive_read_register_format(a, mtree, "mtree", mtree_bid, NULL,
                                     read_header, read_data, skip, NULL,
                                     cleanup);
}
#include "tar/he_creation_set.h"
void main(int argc, char **argv) {
  struct bsdtar *bsdtar, bsdtar_storage;
  int opt, t;
  bsdtar = &bsdtar_storage;
  memset(bsdtar, 0, sizeof *bsdtar);
  bsdtar->cset = cset_new();
  if (bsdtar->cset == NULL)
    lafe_errc(1, errno, "Out of memory");
  bsdtar->argv = argv;
  while ((opt = bsdtar_getopt(bsdtar)) != -1) {
    switch (opt) {
    case 'f':
      bsdtar->filename = bsdtar->argument;
      break;
    case 't':
      set_mode(bsdtar, opt);
    }
  }
  if (cset_get_format(bsdtar->cset) != NULL)
    only_mode(bsdtar, "--format", "cru");
  switch (bsdtar->mode) {
  case 't':
    tar_mode_t(bsdtar);
  }
}
