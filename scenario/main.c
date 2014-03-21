/*This program to draw points, Lines and polygons*/
#include <GLUT/glut.h>
#include <math.h>
#include "main.h"

int main(int argc, char** argv)
{
    glutInit(&argc,argv);                                   /*initialize the toolkit   */
    glutInitWindowSize( 1000, 750 );                         /* Set window size */
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE);           /* Set the display mode */
    glutInitWindowPosition( 500, 100 );
    glutCreateWindow("Back When Life Was Simple");

    glutDisplayFunc(display);                               /*tell OpenGL main loop what*/
    glutMouseFunc(mouse);
    myinit();                                               /* set attributes                 */

    glutMainLoop();                                         /* pass control to the main loop  */
}
