//
//  main.c
//  introduction
//
//  Created by Chintak Sheth on 23/09/13.
//  Copyright (c) 2013 Chintak Sheth. All rights reserved.
//

/*This program to draw points, Lines and polygons*/
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <math.h>
#include "main.h"

int main(int argc, char** argv)
{
    glutInit(&argc,argv);                                   /*initialize the toolkit   */
    glutInitWindowSize( 500, 500 );                         /* Set window size */
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE);           /* Set the display mode */
    glutInitWindowPosition( 500, 100 );
    glutCreateWindow("My First Graphics Program in OpenGL");                          /* create window with title */
    
    glutDisplayFunc(display);                               /*tell OpenGL main loop what     */
    myinit();                                               /* set attributes                 */
    
    glutMainLoop();                                         /* pass control to the main loop  */
}
