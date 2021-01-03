#ifndef _EXTENDED_MATH_BASE_H_
#define _EXTENDED_MATH_BASE_H_

#include <math.h>

#define EM_PI 3.141592653589793f

typedef struct{  // PairInt
    int x;
    int y;
}PairInt;

typedef struct{  // Cartesian coordinates
    float x;
    float y;
}Cartesian;
typedef struct{  // Polar coordinates
    float r;
    float theta;
}Polar;

#endif
