#pragma once

typedef struct Codefile {
  int lines;
  int filetype;
} codefile_t;

codefile_t change_filetype(codefile_t *f, int new_filetype);
