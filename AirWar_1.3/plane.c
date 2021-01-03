#include <stdbool.h>

#include "basic_settings.h"

#include <math.h>
#include "extended_math.h"

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include "plane_base.h"



// d_{...}: d{...} / dt * 1 ms

const GLfloat d_orientation = 1e-3;
const GLfloat d_velocity = 1e-5;

// Drag Coefficients
typedef struct{  // Drag_Rotate_Weights
    float orientation;
    float velocity;
} Drag_Rotate_Weights;
const struct{
    struct{  // rotate
        float range;  // cosine
        Drag_Rotate_Weights stability;
        Drag_Rotate_Weights instability;
    } rotate;
    struct{
        float range;  // cosine
        float weight;
    } decelerate;
} drag_coefficients = {
    {  // rotate
        .8, {1e-3, 3e-3}, {2e-3, 1e-4}
    },
    {  // decelerate
        .98, 7e-1
    }
};



void initialize_plane(Plane* plane){
    plane->position.x = 0.;
    plane->position.y = 0.;
    plane->orientation = 0.;
    plane->velocity.r = 0.;
    plane->velocity.theta = 0.;
}

char key_to_direction(int key, bool is_normal){
    char direction = '\0';
    
    if(is_normal){
        switch(key){
            case 'w': case 'i':
                direction = 'u'; break;
            case 'a': case 'j':
                direction = 'l'; break;
            case 's': case 'k':
                direction = 'd'; break;
            case 'd': case 'l':
                direction = 'r'; break;
        }
    }
    else{
        switch(key){
            case GLUT_KEY_UP:
                direction = 'u'; break;
            case GLUT_KEY_LEFT:
                direction = 'l'; break;
            case GLUT_KEY_DOWN:
                direction = 'd'; break;
            case GLUT_KEY_RIGHT:
                direction = 'r'; break;
        }
    }
    
    return direction;
}

void set_plane_velocity(Plane* plane, char direction){
    switch(direction){
        case 'u':{
            add_to_vector_a(&(plane->velocity),
                d_velocity * Refresh_Period, plane->orientation);
            break;
        }
        case 'd':{
            if(plane->velocity.r < 2 * d_velocity * Refresh_Period)
                plane->velocity.r = 0.;
            else if(cos(plane->velocity.theta - plane->orientation) > 0){
                add_to_vector_a(&(plane->velocity),
                    -d_velocity * Refresh_Period, plane->orientation);
            }
            else{
                add_to_vector_a(&(plane->velocity),
                    0.2 * d_velocity * Refresh_Period, plane->orientation);
            }
            break;
        }
        case 'l': plane->orientation += d_orientation * Refresh_Period; break;
        case 'r': plane->orientation -= d_orientation * Refresh_Period; break;
    }
    
    plane->orientation = standardize_angle(plane->orientation);
    standardize_polar(&(plane->velocity));
}

void move_plane(Plane* plane){
    float delta_angle = plane->velocity.theta - plane->orientation;
    
    // Drag (rotate)
    if(cos(delta_angle) > drag_coefficients.rotate.range){
        float tmp = sin(delta_angle);
        plane->orientation +=
            drag_coefficients.rotate.stability.orientation *
            tmp * Refresh_Period;
        plane->velocity.theta -=
            drag_coefficients.rotate.stability.velocity *
            tmp * Refresh_Period;
    }
    else{
        float tmp =
            (1. + cos(delta_angle)) * sign(-sin(delta_angle)) *
            atan(plane->velocity.r / d_velocity / Refresh_Period / 6);
        plane->orientation +=
            drag_coefficients.rotate.instability.orientation * tmp * Refresh_Period;
        plane->velocity.theta -=
            drag_coefficients.rotate.instability.velocity * tmp * Refresh_Period;
    }
    
    // Drag (decelerate)
    if(cos(delta_angle) < drag_coefficients.decelerate.range){
        float tmp =
            (drag_coefficients.decelerate.range - cos(delta_angle)) /
            (drag_coefficients.decelerate.range + 1);
        if(plane->velocity.r < 2 * d_velocity * Refresh_Period)
            plane->velocity.r = 0.;
        else{
            add_to_vector_a(&(plane->velocity),
                -d_velocity * Refresh_Period *
                drag_coefficients.decelerate.weight * exp(tmp),
                plane->velocity.theta);
        }
    }
    
    // Move
    plane->position.x += plane->velocity.r * cos(plane->velocity.theta) * Refresh_Period;
    plane->position.y += plane->velocity.r * sin(plane->velocity.theta) * Refresh_Period;
    
    if(plane->position.x > position_range.x)
        plane->position.x = -position_range.x;
    else if(plane->position.x < -position_range.x)
        plane->position.x = position_range.x;
    if(plane->position.y > position_range.y)
        plane->position.y = -position_range.y;
    else if(plane->position.y < -position_range.y)
        plane->position.y = position_range.y;
}

