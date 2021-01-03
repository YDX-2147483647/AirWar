#ifndef _PLANE_BASE_H_
#define _PLANE_BASE_H_

#include <stdbool.h>
#include "extended_math.h"

typedef struct{  // Plane
    Cartesian position;
    Polar velocity;
    float orientation;
}Plane;

#endif

