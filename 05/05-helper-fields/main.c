#include <stdint.h>
#include <stdio.h>

typedef union RgbaColor {
  struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
  } components;
  uint32_t value;
} rgba_color_t;

int main() {
  rgba_color_t red = {
      .components =
          {
              .r = 0xff,
              .g = 0x01,
              .b = 0x02,
              .a = 0x03,
          },
  };

  printf("red.value: %.6x\n", red.value);
  printf("red.components.r: %.2x\n", red.components.r);
  printf("red.components.b: %.2x\n", red.components.b);
  printf("red.components.g: %.2x\n", red.components.g);
  printf("red.components.a: %.2x\n", red.components.a);
}
