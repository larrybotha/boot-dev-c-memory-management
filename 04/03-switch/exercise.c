#include "exercise.h"
#include <stdlib.h>

char *http_to_str(http_status_t status) {
  switch (status) {
  case HTTP_OK:
    return "200 Ok";
  case HTTP_IM_A_TEAPOT:
    return "218 I'm a teapot";
  case HTTP_NOT_FOUND:
    return "404 Not found";
  };

  return NULL;
}
