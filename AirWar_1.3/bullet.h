#ifndef _BULLET_H_
#define _BULLET_H_

#include "bullet_base.h"
#include "plane_base.h"

extern void initialize_bullets(Bullet bullets[]);
extern Bullet* allocate_bullet(Bullet bullets[]);
extern void set_bullet(Bullet* bullet, const Plane* plane);
extern void move_bullets(Bullet bullets[]);

#endif
