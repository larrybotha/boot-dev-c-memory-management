#include "../../munit/munit.h"

#include "exercise.h"

MunitResult test_packet_header_size(const MunitParameter params[],
                                    void *user_data_or_fixture) {
  munit_assert_size(sizeof(packet_header_t), ==, 8);

  return MUNIT_OK;
}

MunitResult test_tcp_header_fields(const MunitParameter params[],
                                   void *user_data_or_fixture) {
  packet_header_t header;

  header.tcp_header.src_port = 0x1234;
  header.tcp_header.dest_port = 0x5678;
  header.tcp_header.seq_num = 0x9abcdef0;

  munit_assert_uint16(header.tcp_header.src_port, ==, 0x1234);
  munit_assert_uint16(header.tcp_header.dest_port, ==, 0x5678);
  munit_assert_uint32(header.tcp_header.seq_num, ==, 0x9abcdef0);

  return MUNIT_OK;
}

int main(int argc, char *argv[]) {
  MunitTest tests[] = {
      {
          "/test_packet_header_size",
          test_packet_header_size,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
      {
          "/test_tcp_header_fields",
          test_tcp_header_fields,
          NULL,
          NULL,
          MUNIT_TEST_OPTION_NONE,
          NULL,
      },
  };

  MunitSuite suite = {
      "header-helpers",
      tests,
      NULL,
      1,
      (MunitSuiteOptions)MUNIT_TEST_OPTION_NONE,
  };

  return munit_suite_main(&suite, NULL, argc, (char *const *)argv);
}
