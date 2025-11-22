#pragma once

typedef enum HttpStatus {
  HTTP_OK = 200,
  HTTP_CREATED, // implicit, incremented
  HTTP_IM_A_TEAPOT = 218,
  HTTP_BAD_REQUEST = 400,
  HTTP_UNAUTHORISED,
  HTTP_PAYMENT_REQUIRED,
  HTTP_FORBIDDEN,
  HTTP_NOT_FOUND,
} http_status_t;

