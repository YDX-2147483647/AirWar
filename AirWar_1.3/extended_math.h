#ifndef _EXTENDED_MATH_H_
#define _EXTENDED_MATH_H_

#include "extended_math_base.h"

extern double degrees(double x);
extern double radians(double x);

extern int sign(double x);

extern double standardize_angle(double a);
extern void standardize_polar(Polar* z);
extern void add_to_vector_a(Polar* u, double k, double a);  // u += k Exp[i a]
extern void add_to_vector_p(Polar* u, double k, Polar v);  // u += k v

extern double distance_between(Cartesian p, Cartesian q);

#endif
