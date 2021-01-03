#ifndef _TARGET_BASE_H_
#define _TARGET_BASE_H_

#include "extended_math.h"

typedef enum{  // Target_LifeCycle
    Target_Birth, Target_Main, Target_Explosion
}Target_LifeCycle;

typedef struct{  // Color
    float r;
    float g;
    float b;
    float a;
}Color;

typedef struct{  // Target
    Target_LifeCycle life_cycle;
    Cartesian position;
    struct{
        float min;
        float max;
    } radius;
    Color color;
}Target;

#endif
