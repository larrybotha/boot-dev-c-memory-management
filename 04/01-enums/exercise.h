//#include <stdlib.h>

typedef enum Colors {
  RED,
  GREEN,
  BLUE,
} colors_t;

typedef struct TrafficLight {
  colors_t state;
} traffic_light_t;

traffic_light_t *new_traffic_light();
