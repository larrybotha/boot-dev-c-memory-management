#pragma once

#include <stdint.h>

typedef union PacketHeader {
  struct {
    uint16_t src_port;
    uint16_t dest_port;
    uint32_t seq_num;
  } tcp_header;
 uint64_t raw;
} packet_header_t;
