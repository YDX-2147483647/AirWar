#include <math.h>
#include "extended_math_base.h"

// Private
double squared(double x){
    return x * x;
}

double cosine_theorem(double a, double C, double b){
    return sqrt(a*a + b*b - 2 * a * b * cos(C));
}


// Public
double degrees(double x){
    return x / EM_PI * 180;
}
double radians(double x){
    return x / 180 * EM_PI;
}

int sign(double x){
//    if(x < 1e-15)
//        return 0;
    return x>0? 1: -1;
}

double standardize_angle(double a){
    while(a > EM_PI)
        a -= 2 * EM_PI;
    while(a < -EM_PI)
        a += 2 * EM_PI;
    return a;
}
void standardize_polar(Polar* z){
    if(z->r < 0.){
        z->r *= -1;
        z->theta += 2 * EM_PI;
    }
    z->theta = standardize_angle(z->theta);
}

void add_to_vector_a(Polar* u, double k, double a){
    Polar tmp = {u->r, a - u->theta};
    u->r = cosine_theorem(tmp.r, EM_PI - tmp.theta, k);
    u->theta = u->theta + 
        atan2(k * sin(tmp.theta), tmp.r + k * cos(tmp.theta));
    
    standardize_polar(u);
}
void add_to_vector_p(Polar* u, double k, Polar v){
    add_to_vector_a(u, k * v.r, v.theta);
}

double distance_between(Cartesian p, Cartesian q){
    return sqrt(squared(p.x - q.x) + squared(p.y - q.y));
}

