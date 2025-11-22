#pragma once

typedef enum {
  HTTP_OK = 200,
  HTTP_IM_A_TEAPOT = 218,
  HTTP_NOT_FOUND = 404
} http_status_t;

char *http_to_str(http_status_t status);
