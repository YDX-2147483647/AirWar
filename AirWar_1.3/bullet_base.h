#ifndef _BULLET_BASE_H_
#define _BULLET_BASE_H_

#include <stdbool.h>
#include "extended_math.h"

typedef struct{  // Bullet
    Cartesian position;
    Polar velocity;
    float orientation;
    bool is_used;
}Bullet;

#define Total_Bullet 6

#endif
