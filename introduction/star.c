//
//  star.c
//  introduction
//
//  Created by Chintak Sheth on 27/09/13.
//  Copyright (c) 2013 Chintak Sheth. All rights reserved.

/*This program to draw points, Lines and polygons*/
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <math.h>
#define B 750

void draw_diamond(int *v1, int *v2, int *v3, int *v4)
{
    glBegin(GL_QUADS);
    glColor3f ( 0.0, 1.0, 0.0);  // Default color is WHITE
    glVertex2iv(v1);
    glColor3f ( 0.0, 0.0, 1.0);
    glVertex2iv(v2);
    glColor3f ( 1.0, 0.0, 0.0);
    glVertex2iv(v3);
    glColor3f ( 0.0, 0.0, 1.0);
    glVertex2iv(v4);
    glEnd();
}
void myinit(void)
{
    glClearColor(0.8, 0.8, 0.8, 0.0); /* gray background */
    
    glMatrixMode(GL_PROJECTION);      /* In World coordinates: */
    glLoadIdentity();                 /* position the "clipping rectangle" */
    gluOrtho2D( -B, B, -B, B);/* at -B/2, its right edge at +B/2, its bottom */
    glMatrixMode(GL_MODELVIEW);       /* edge at -B/2 and its top edge at +B/2 */
}

void display( void )
{
    glClear(GL_COLOR_BUFFER_BIT);     /*clear the window */
    
    glMatrixMode(GL_MODELVIEW);       /* The following coordinates are expressed */
    glLoadIdentity();                 /* in terms of World coordinates */
    int v1[] = {0, 0};
    int v2[] = {53, 67};
    int v3[] = {0, 200};
    int v4[] = {-53, 67};
    int i;
    
    glEnable(GL_POINT_SMOOTH);
    
    draw_diamond(v1, v2, v3, v4);
    glPushMatrix();
        for(i=0; i<4; i++)
        {
            glRotatef(72, 0, 0, 1);
            draw_diamond(v1, v2, v3, v4);
        }
    glPopMatrix();
    
    glFlush();                       /* send all commands */
}
