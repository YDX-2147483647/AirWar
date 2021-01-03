#ifndef _PLANE_H_
#define _PLANE_H_

#include "plane_base.h"
#include "extended_math.h"

// Plane's shape
enum{
    plane_shape_length_0 = 6,
    plane_shape_length_1 = 5
};
const Cartesian plane_shape[plane_shape_length_0][plane_shape_length_1] = {
    {{0, 5}, {-.4, 4}, {-.5, 2.5}, {0, 2.5}, {.0, 2.5}},
    {{-.6, 3.4}, {-.8, 0}, {-.5, -4}, {0, -4}, {0, 3.2}},
    {{-.8, 3}, {-1.8, 2}, {-1.6, 1.5}, {0, 2}, {0, 3}},
    {{0, 0.5}, {-5, -2.5}, {-5, -3}, {0, -3.3}, {0, -3.3}},
    {{-.5, -2}, {-1.5, -4.5}, {-1.2, -4.8}, {0, -3.5}, {0, -3.5}},
    {{-.5, -4}, {-.4, -4.5}, {-.1, -4.5}, {0, -4}, {0, -4}}
};

extern void initialize_plane(Plane* plane);
// Control
extern char key_to_direction(int key, bool is_normal);
extern void set_plane_velocity(Plane* plane, char direction);
extern void move_plane(Plane* plane);

#endif 

