#include <stdio.h>
#include <stdbool.h>

#include "basic_settings.h"

#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <GL/glut.h>

#include "extended_math.h"
#include "plane.h"
#include "bullet.h"
#include "target.h"



int world_size = 1024;
PairInt screen = {1024, 576};

int score = -1;
char score_string[12];

Plane plane;
Bullet bullets[Total_Bullet];
Target target;



void update_score(){
    score += 1;
    sprintf(score_string, "SCORE: %2d", score);
}



void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Write the score;
    glLineWidth(6.0);
    glColor3f(0.15, 0.5, 1.);
    glPushMatrix();
        glScalef(2e-6 * screen.y, 2e-6 * screen.x, 0.);
        glTranslatef(-400., -50., 0.);
        
        for(char* c = score_string; *c != '\0'; c++)
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    glPopMatrix();
    
    
    // Draw the target.
    glPushMatrix();
    
    glScalef(4e-5 * screen.y, 4e-5 * screen.x, 0.);
    glTranslatef(target.position.x, target.position.y, 0.);
    glColor4f(target.color.r, target.color.g, target.color.b, target.color.a);
    
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0., 0.);
        for(float i = -EM_PI; i < EM_PI; i += EM_PI/16){
            glVertex2f(target.radius.min * cos(i),
                target.radius.min * sin(i));
            glVertex2f(target.radius.max * cos(i + EM_PI/32),
                target.radius.max * sin(i + EM_PI/32));
        }
        glVertex2f(-target.radius.min, 0);
    glEnd();
    
    glPopMatrix();
    
    
    // Draw bullets.
    for(int i=0; i < Total_Bullet; i++){
        if(bullets[i].is_used){
            glPushMatrix();
            
            glScalef(4e-5 * screen.y, 4e-5 * screen.x, 0.);
            glTranslatef(bullets[i].position.x, bullets[i].position.y, 0.);
            glRotatef(degrees(bullets[i].orientation), 0., 0., 1.);
            
            glLineWidth(5.);
            glBegin(GL_LINES);
                glColor4f(1., 0., 0., 1.);
                glVertex2f(0., 0.);
                glColor4f(0., 0., 0., 0.);
                glVertex2f(-3., 0.);
            glEnd();
            
            glPopMatrix();
        }
    }
    
    
    // Draw the plane.
    glPushMatrix();
    
    glScalef(4e-5 * screen.y, 4e-5 * screen.x, 0.);
    glTranslatef(plane.position.x, plane.position.y, 0.);
    glRotatef(degrees(plane.orientation) - 90, 0., 0., 1.);
    
    glColor3f(1., 1., 1.);
    for(int i=0; i<plane_shape_length_0; i++){
        for(int side=1; side >= -1; side -= 2){
            glBegin(GL_POLYGON);
            for(int j=0; j<plane_shape_length_1; j++)
                glVertex2f(plane_shape[i][j].x * side,
                    plane_shape[i][j].y);
            glEnd();
        }
    }
    
    glPopMatrix();
    
    
    glutSwapBuffers();
}

void timer(int value){
    move_plane(&plane);
    move_bullets(bullets);
    update_target(&target, bullets, update_score);
    
    glutPostRedisplay();
    glutTimerFunc(Refresh_Period, timer, 0);
}

void key_callback_normal(unsigned char key, int mouse_x, int mouse_y){
    char direction = key_to_direction(key, true);
    if(direction != '\0')
        set_plane_velocity(&plane, direction);
    else if(key == ' '){
        Bullet* b = allocate_bullet(bullets);
        if(b != NULL)
            set_bullet(b, &plane);
    }
}

void key_callback_special(int key, int mouse_x, int mouse_y){
    set_plane_velocity(&plane, key_to_direction(key, false));
}



int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(screen.x, screen.y);
//    glutInitWindowSize(world_size, world_size);
//    glOrtho(-100,100,-100,100,0,0);
//    glViewport(0, 0,512, 768);
    glutCreateWindow("Air War - 1.3 | Y.D.X.");
    
    initialize_plane(&plane);
    initialize_bullets(bullets);
    update_score();
    initialize_target(&target);
    
    glutKeyboardFunc(key_callback_normal);
    glutSpecialFunc(key_callback_special);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glutDisplayFunc(display);
    glutTimerFunc(Refresh_Period, timer, 0);
    
    glutMainLoop();
    
    return 0;
}
