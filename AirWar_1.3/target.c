#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "basic_settings.h"

#include <math.h>
#include "extended_math.h"

#include "target_base.h"
#include "bullet_base.h"



const float unit_radius = 2.;
const float fade_speed = 1e-3; 



// Public
void initialize_target(Target* target){
    srand((unsigned) time(NULL));
    target->life_cycle = Target_Birth;
}

void update_target(Target* target, Bullet bullets[], void(*on_hit)(void)){
    switch(target->life_cycle){
        case Target_Birth:{
            target->position.x =
                position_range.x * (1.6 * rand() / RAND_MAX - 0.8);
            target->position.y =
                position_range.y * (1.6 * rand() / RAND_MAX - 0.8);
            target->radius.min = unit_radius;
            target->radius.max = unit_radius;
            target->color.r = .2 + .6 * rand() / RAND_MAX;
            target->color.g = .2 + .6 * rand() / RAND_MAX;
            target->color.b = .2 + .6 * rand() / RAND_MAX;
            target->color.a = 1.;
            
            target->life_cycle = Target_Main;
            break;
        }
        case Target_Main:{
            for(int i=0; i < Total_Bullet; i++){
                if(bullets[i].is_used){
                    bool is_hit = false;
                    is_hit |= target->radius.max * 1.2 >
                        distance_between(target->position, bullets[i].position);
                    
                    if(is_hit){
                        target->life_cycle = Target_Explosion;
                        on_hit();
                        bullets[i].is_used = false;
                        target->radius.max = 5 * unit_radius;
                        break;
                    }
                }
            }
            break;
        }
        case Target_Explosion:{
            target->color.a -= fade_speed * Refresh_Period;
            if(target->color.a <= 0.)
                target->life_cycle = Target_Birth;
            break;
        }
    }
}

