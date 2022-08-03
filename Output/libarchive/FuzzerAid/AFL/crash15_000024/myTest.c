#include "libarchive/he_archive_read_support_format_mtree.h"
int process_add_entry(struct archive_read *a, struct mtree *mtree,
                      struct mtree_option **global, const char *line,
                      ssize_t line_len, struct mtree_entry **last_entry,
                      int is_form_d) {
  struct mtree_entry *entry;
  const char next, eq, name, end;
  size_t len;
  memcpy(entry->name, name, len);
}
int read_mtree(struct archive_read *a, struct mtree *mtree) {
  ssize_t len;
  uintmax_t counter;
  char *p;
  int global, last_entry, r, is_form_d;
  for (counter = 1;; ++counter) {
    if (*p != '/') {
      r = process_add_entry(a, mtree, &global, p, len, &last_entry, is_form_d);
    }
  }
}
int read_header(struct archive_read *a, struct archive_entry *entry) {
  struct mtree *mtree;
  int r, use_next;
  if (mtree->fd >= 0) {
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
#include "tar/he_bsdtar.h"
int main(int argc, char **argv) {
  struct bsdtar *bsdtar, bsdtar_storage;
  int opt, t;
  bsdtar = &bsdtar_storage;
  memset(bsdtar, 0, sizeof *bsdtar);
  bsdtar->matching = archive_match_new();
  bsdtar->cset = cset_new();
  bsdtar->argv = argv;
  while ((opt = bsdtar_getopt(bsdtar)) != -1) {
    switch (opt) {
    case 'f':
      bsdtar->filename = bsdtar->argument;
      if (archive_match_include_file_time(
              bsdtar->matching, ARCHIVE_MATCH_CTIME | ARCHIVE_MATCH_NEWER,
              bsdtar->argument) != ARCHIVE_OK)
      case 't':
        set_mode(bsdtar, opt);
    }
  }
  switch (bsdtar->mode) {
  case 't':
    tar_mode_t(bsdtar);
  }
}
