#ifndef _TARGET_H_
#define _TARGET_H_

#include "target_base.h"
#include "bullet_base.h"

extern void initialize_target(Target* target);
extern void update_target(Target* target,
    Bullet bullets[], void(*on_hit)(void));

#endif
