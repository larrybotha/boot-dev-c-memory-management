#include "exercise.h"

codefile_t change_filetype(codefile_t *f, int new_filetype) {
  f->filetype = new_filetype;

  return *f;
};
