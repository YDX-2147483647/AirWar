#include <stdio.h>
#include <stdbool.h>

#include "basic_settings.h"

#include <math.h>
#include "extended_math.h"

#include "bullet_base.h"
#include "plane_base.h"



const float initial_bullet_speed = 2e-2;



// Private
void initialize_bullet(Bullet* bullet){
    bullet->position.x = 0.;
    bullet->position.y = 0.;
    bullet->orientation = 0.;
    bullet->velocity.r = 0.;
    bullet->velocity.theta = 0.;
    bullet->is_used = false;
}

void move_bullet(Bullet* bullet){
    if(bullet->is_used){
        bullet->position.x += bullet->velocity.r * cos(bullet->velocity.theta) * Refresh_Period;
        bullet->position.y += bullet->velocity.r * sin(bullet->velocity.theta) * Refresh_Period;
        
        if(fabs(bullet->position.x) > position_range.x ||
        fabs(bullet->position.y) > position_range.y){
            bullet->is_used = false;
        }
    }
}


// Public
void initialize_bullets(Bullet bullets[]){
    for(int i=0; i < Total_Bullet; i++){
        initialize_bullet(&(bullets[i]));
    }
}

Bullet* allocate_bullet(Bullet bullets[]){
    for(int i=0; i < Total_Bullet; i++){
        if(!bullets[i].is_used)
            return &(bullets[i]);
    }
    return NULL;
}

void set_bullet(Bullet* bullet, const Plane* plane){
    if(bullet != NULL){
        bullet->is_used = true;
        bullet->position = plane->position;
        bullet->velocity = plane->velocity;
        add_to_vector_a(&(bullet->velocity),
            initial_bullet_speed, plane->orientation);
        bullet->orientation = plane->orientation;
    }
}

void move_bullets(Bullet bullets[]){
    for(int i=0; i < Total_Bullet; i++)
        move_bullet(&(bullets[i]));
}

