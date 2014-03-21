/*This program to draw points, Lines and polygons*/
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define b 5
#define a 7.2
#define NUM_STEPS 200
#define DEG2RAD 0.0174532925
#define NUM_PARTICLES    1200          /* Number of particles  */
#define NUM_DEBRIS       170            /* Number of debris     */

/* A particle */
struct particleData
{
   float position[3];
   float speed[3];
   float color[3];
};
typedef struct particleData particleData;

/* A piece of debris */

struct debrisData
{
   float position[3];
   float speed[3];
   float orientation[3];        /* Rotation angles around x, y, and z axes */
   float orientationSpeed[3];
   float color[3];
   float scale[3];
};
typedef struct debrisData debrisData;

particleData particles[NUM_PARTICLES];
debrisData debris[NUM_DEBRIS];
int fuel = 0, inc=0, l=0, flag1=0, rocket = 0;
float match = 0;                /* "fuel" of the explosion */
float cam_angle = 0.0;             /* camera rotation angle */
GLuint startList, cracker, greeting, flicker = 0, particlesRotate = 0, flag=0, i=0, card1;
GLuint crackerSubMenu[] = {0,0,0}, greetingSubMenu[] = {0,0,0};
int startAngle = -90;
GLuint step=0, blow=0;
GLfloat traj[NUM_STEPS][2];
float startx=0, starty=0, sx=0, sy=0;
GLfloat menuHover, cardOpen = 0, angle = 4;
char crackerText[] = "Crackers", blast[] = "Blast!";
char greetingText[] = "Greeting Cards", input[30], name[10];
char msg[] = "Enter your message and press Enter";
char msg1[]="Enter your name and press Enter";
char from[]="Wishes From";

GLfloat  light0Amb[4] =  { 1.0, 0.6, 0.2, 1.0 };
GLfloat  light0Dif[4] =  { 1.0, 0.6, 0.2, 1.0 };
GLfloat  light0Spec[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat  light0Pos[4] =  { 0.0, 0.0, 0.0, 1.0 };

GLfloat  light1Amb[4] =  { 0.0, 0.0, 0.0, 1.0 };
GLfloat  light1Dif[4] =  { 1.0, 1.0, 1.0, 1.0 };
GLfloat  light1Spec[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat  light1Pos[4] =  { 0.0, 5.0, 5.0, 0.0 };

GLfloat  materialAmb[4] = { 0.25, 0.22, 0.26, 1.0 };
GLfloat  materialDif[4] = { 0.63, 0.57, 0.60, 1.0 };
GLfloat  materialSpec[4] = { 0.99, 0.91, 0.81, 1.0 };
GLfloat  materialShininess = 27.8;


void myinit(void)
{
   GLuint i=0, j=0;
   GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 0.0, 5.0, 4.0, 0.0 };
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat model_ambient[] = { 0.5, 0.5, 0.5, 1.0 };

   glClearColor(0.0, 0.0, 0.0, 0.0);

   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

   /* Create 4 display lists, each with a different quadric object.
    * Different drawing styles and surface normal specifications
    * are demonstrated.
    */

   // cylinder();
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho (-5.0, 5.0, -5.0, 5.0, -5, 5);
   glMatrixMode (GL_MODELVIEW);

   for(i = 1; i < NUM_STEPS; i++)
   {
       traj[i][1] = (i * 6.)/NUM_STEPS;
       traj[i][0] = traj[i][1] * traj[i][1];
   }
}


void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho (-5.0, 5.0, -5.0, 5.0, -5, 5);
   glMatrixMode (GL_MODELVIEW);
}


void errorCallback(GLenum errorCode)
{
   const GLubyte *estring;

   estring = gluErrorString(errorCode);
   fprintf(stderr, "Quadric Error: %s\n", estring);
   exit(0);
}

void func(void)
{
   int i;
   if (fuel > 0)
   {
       for (i = 0; i < NUM_PARTICLES; i++)
       {
           particles[i].position[0] += particles[i].speed[0] * 0.05;
           particles[i].position[1] += particles[i].speed[1] * 0.05;
           particles[i].position[2] += particles[i].speed[2] * 0.05;

           particles[i].color[0] -= 1.0 / 500.0;
           if (particles[i].color[0] < 0.0)
           {
               particles[i].color[0] = 0.0;
           }

           particles[i].color[1] -= 1.0 / 100.0;
           if (particles[i].color[1] < 0.0)
           {
               particles[i].color[1] = 0.0;
           }

           particles[i].color[2] -= 1.0 / 50.0;
           if (particles[i].color[2] < 0.0)
           {
               particles[i].color[2] = 0.0;
           }
       }

       for (i = 0; i < NUM_DEBRIS; i++)
       {
           debris[i].position[0] += debris[i].speed[0] * 0.02;
           debris[i].position[1] += debris[i].speed[1] * 0.02;
           debris[i].position[2] += debris[i].speed[2] * 0.02;

           debris[i].orientation[0] += debris[i].orientationSpeed[0] * 10;
           debris[i].orientation[1] += debris[i].orientationSpeed[1] * 10;
           debris[i].orientation[2] += debris[i].orientationSpeed[2] * 10;
       }
   }

   cam_angle += 0.03;  /* Always continue to rotate the camera */
   glutPostRedisplay ();
}


void newSpeed(float dest[3])
{
   float x, y, z, len;

   x = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
   y = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
   z = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

   /*
   * Normalizing the speed vectors gives a "fireball" effect
   *
   */

   len = sqrt (x * x + y * y + z * z);

   if (len)
   {
       x = x / len;
       y = y / len;
       z = z / len;
   }

   dest[0] = x;
   dest[1] = y;
   dest[2] = z;
}


void newExplosion (void)
{
   int i;

   for (i = 0; i < NUM_PARTICLES; i++)
   {
       particles[i].position[0] = 0.0;
       particles[i].position[1] = 0.0;
       particles[i].position[2] = 0.0;

       particles[i].color[0] = 1.0;
       particles[i].color[1] = 1.0;
       particles[i].color[2] = 0.5;

       newSpeed (particles[i].speed);
   }

   for (i = 0; i < NUM_DEBRIS; i++)
   {
       debris[i].position[0] = 0.0;
       debris[i].position[1] = 0.0;
       debris[i].position[2] = 0.0;

       debris[i].orientation[0] = 0.0;
       debris[i].orientation[1] = 0.0;
       debris[i].orientation[2] = 0.0;

       debris[i].color[0] = 0.7;
       debris[i].color[1] = 0.7;
       debris[i].color[2] = 0.7;

       debris[i].scale[0] = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
       debris[i].scale[1] = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
       debris[i].scale[2] = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

       newSpeed (debris[i].speed);
       newSpeed (debris[i].orientationSpeed);
   }

   fuel = 100;
}


void cylinder()
{
   GLfloat cylin_diff[] = { 1., particlesRotate%10 / 10., 0, 1.0 };
   GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };

   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, cylin_diff);

   GLUquadricObj *qobj;
   startList = glGenLists(1);
   qobj = gluNewQuadric();

   gluQuadricDrawStyle(qobj, GLU_FILL); /* flat shaded */
   gluQuadricNormals(qobj, GLU_FLAT);
   glNewList(startList, GL_COMPILE);
   glTranslatef(1,-.15,-.1);
   glRotatef(-90,1,0,0);
   gluCylinder(qobj, 0.5, 0.1, 1.0, 15, 15);
   glEndList();
}


void circle(float x1, float y1, float radiusx,float radiusy, float start,float result, int flag)
{
   float x2,y2;
   float angle;

   glEnable(GL_POINT_SMOOTH);
   glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
   glPointSize(radiusx);

   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(x1,y1,2.15);
   if(flag == 1)
   {
       glColor4f(228/255.,255/255.,0/255.,cardOpen);
       if(flicker % 10 > 5)
           glColor4f(252/255.,168/255.,0/255., cardOpen);
   }
   for (angle=start;angle<result;angle+=.01)
   {

       x2 = x1+sin(angle)*radiusx;
       y2 = y1+cos(angle)*radiusy;
       glVertex3f(x2,y2,2.15);
   }

   glEnd();
}


void arc(float x1, float y1, float radiusx,float radiusy, float start,float result, int flag)
{
   float x2,y2;
   float angle;

   glEnable(GL_POINT_SMOOTH);
   glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
   glPointSize(radiusx);

   glBegin(GL_LINE_STRIP);
   if(flag == 1)
   {
       glColor4f(228/255.,255/255.,0/255.,1);
       if(flicker % 10 > 5)
           glColor4f(252/255.,168/255.,0/255., 1);
   }
   for (angle=start;angle<result;angle+=.01)
   {
       x2 = x1+sin(angle)*radiusx;
       y2 = y1+cos(angle)*radiusy;
       glVertex3f(x2,y2,2.15);
   }

   glEnd();
}


void anar_particles(float coef)
/* Implements x = A*y^2 function to generate trajectories */
{
   glDisable(GL_LIGHTING);
   GLuint j=5;
   glEnable(GL_POINT_SMOOTH);
   glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

   for(j=0; j<=NUM_STEPS; j+=5)
   {
       if(step >= j)
       {
           glColor4f(1., ((step-j)%NUM_STEPS)/(NUM_STEPS*1.), 0, 1.-((step-j)%NUM_STEPS)/(NUM_STEPS*1.));

           glPushMatrix();
           glTranslatef(0, 0, 3);
           circle(coef*traj[(step-j)%NUM_STEPS][0], traj[(step-j)%NUM_STEPS][1], .05, .1, 0, 10, 0);
           glPopMatrix();

           glColor4f(1., ((step-j)%NUM_STEPS)/(NUM_STEPS*1.), 0, 1.);
           glPushMatrix();
           glTranslatef(coef*traj[(step-j)%NUM_STEPS][0], traj[(step-j)%NUM_STEPS][1], 0);
           glutSolidSphere(.05, 56, 56);
           glPopMatrix();
       }
   }
   step++;
}


GLuint LoadTexture( const char * filename, int width, int
height )
{
   GLuint texture;
   unsigned char * data;
   FILE * file;

   //The following code will read in our RAW file
   file = fopen( filename, "rb" );
   if ( file == NULL ) return 0;
   data = (unsigned char *)malloc( width * height * 3 );
   fread( data, width * height * 3, 1, file );
   fclose( file );

   glGenTextures( 1, &texture ); //generate the texture with the loaded data
   glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture to it’s array
   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters

   //is far from the view.

   //The qualities are (in order from worst to best)
   //GL_NEAREST
   //GL_LINEAR
   //GL_LINEAR_MIPMAP_NEAREST
   //GL_LINEAR_MIPMAP_LINEAR

   //And if you go and use extensions, you can use Anisotropic filtering textures which are of an
   //even better quality, but this will do for now.
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

   //Here we are setting the parameter to repeat the texture instead of clamping the texture
   //to the edge of our shape.
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

   //Generate the texture
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
   free( data ); //free the texture
   return texture; //return whether it was successfull
}


void FreeTexture( GLuint texture )
{
   glDeleteTextures( 1, &texture );
}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
       case 27:
           exit(0);
           break;
   }

   if(flag1==0)
   {
       if(key==8 || key==127)
       {
           input[l-1]=' ';
           l--;
       }
       else
       {
           input[l]=key;
           l++;
       }
   }

   if(key==13)
   {
       flag1++;
       l=0;
   }

   if(flag1==1)
   {
       if(key==8 || key==127)
       {
           name[l-1]=' ';
           l--;
       }
       else
       {
           name[l]=key;
           l++;
       }
   }
}


void mouseClicks(int key, int state, int x, int y)
{
   if(state == GLUT_DOWN)
   {
       if(x >= 303 && x <= 380 && y >= 256 && y <= 280 && crackerSubMenu[2]==1)
           blow = 1;
        if(x >= 303 && x <= 380 && y >= 256 && y <= 280 && crackerSubMenu[1]==1)
            rocket = 1;

       if(x >= 7 && x <= 201)
       {
           if(y >= 9 && y<= 32)
               cracker = 1 - cracker;  //  Show Crackers Menu
           else if (y >= 33 && y <= 68 && cracker == 1)
           {
               crackerSubMenu[0] = 1;
               crackerSubMenu[1] = 0;
               crackerSubMenu[2] = 0;
               greetingSubMenu[0] = 0;
               greetingSubMenu[1] = 0;
               greetingSubMenu[2] = 0;
               cracker = 0;
               cardOpen= 0;
           }
           else if (y >= 69 && y <= 103 && cracker == 1)
           {
               crackerSubMenu[0] = 0;
               crackerSubMenu[1] = 1;
               crackerSubMenu[2] = 0;
               greetingSubMenu[0] = 0;
               greetingSubMenu[1] = 0;
               greetingSubMenu[2] = 0;
               cracker = 0;
               cardOpen= 0;
               rocket = 0;
               newExplosion ();
           }
           else if (y >= 104 && y <= 139 && cracker == 1)
           {
               crackerSubMenu[0] = 0;
               crackerSubMenu[1] = 0;
               crackerSubMenu[2] = 1;
               greetingSubMenu[0] = 0;
               greetingSubMenu[1] = 0;
               greetingSubMenu[2] = 0;
               cracker = 0;
               cardOpen= 0;
               match = 0;
               blow = 0;
               newExplosion ();
           }
           else cracker = 0;
       }
       else cracker = 0;

       if(x >= 215 && x <= 411)
       {
           if(y >= 9 && y<= 32)
               greeting = 1 - greeting;  //  Show Greeting Cards Menu
           else if (y >= 33 && y <= 68 && greeting == 1)
           {
               crackerSubMenu[0] = 0;
               crackerSubMenu[1] = 0;
               crackerSubMenu[2] = 0;
               greetingSubMenu[0] = 1;
               greetingSubMenu[1] = 0;
               greetingSubMenu[2] = 0;
               greeting = 0;
               cardOpen= 0;
           }
           else if (y >= 69 && y <= 103 && greeting == 1)
           {
               crackerSubMenu[0] = 0;
               crackerSubMenu[1] = 0;
               crackerSubMenu[2] = 0;
               greetingSubMenu[0] = 0;
               greetingSubMenu[1] = 1;
               greetingSubMenu[2] = 0;
               greeting = 0;
               cardOpen= 0;
           }
           else if (y >= 104 && y <= 139 && greeting == 1)
           {
               crackerSubMenu[0] = 0;
               crackerSubMenu[1] = 0;
               crackerSubMenu[2] = 0;
               greetingSubMenu[0] = 0;
               greetingSubMenu[1] = 0;
               greetingSubMenu[2] = 1;
               greeting = 0;
               cardOpen= 0;
           }
           else greeting = 0;
       }
       else greeting = 0;
   }

   glFlush();
}


void mouseMotion(int x, int y)
{
   if(y<= 32)
       menuHover = 1;  //  Crackers
   else menuHover = 0.3;

   glFlush();
}


void crackerMenu()
{
   char styleText1[] = {"Flower Pot"};
   char styleText2[] = {"Rocket"};
   char styleText3[] = {"Bomb"};
   glBegin(GL_QUADS);
   glColor3f(1, 1, 1);
   glVertex3f(-b + .04, a - .53, .18);
   glVertex3f(-b + 2.01, a - .53, .18);
   glVertex3f(-b + 2.01, a - .53 - 2.1, .18);
   glVertex3f(-b + .04, a - .53 - 2.1, .18);
   glEnd();

   glColor4f(.6, .6, .6, .7);
   glBegin(GL_LINES);
   glVertex3f(-b + .04, a - .53 - .7, .18);
   glVertex3f(-b + 2.01, a - .53 - .7, .18);

   glVertex3f(-b + .04, a - .53 - 1.4, .18);
   glVertex3f(-b + 2.01, a - .53 - 1.4, .18);
   glEnd();

   // Icons
   glPushMatrix();
   glTranslatef(-b + .04 + .15, a - .53 - .35, .18);
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_TRIANGLES);
   glVertex3f(0, 0, .3);
   glVertex3f(.2, .5, .3);
   glVertex3f(.4, 0, .3);
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-b + .04 + .15, a - .53 - 1.05, .18);
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_TRIANGLES);
   glVertex3f(0, .25, .3);
   glVertex3f(.2, .5, .3);
   glVertex3f(.4, .25, .3);
   glEnd();

   glBegin(GL_QUADS);
   glVertex3f(.1, 0, .3);
   glVertex3f(.1, .25, .3);
   glVertex3f(.3, .25, .3);
   glVertex3f(.3, 0, .3);
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-b + .04 + .35, a - .53 - 1.75, -1.97);
   glColor3f(1.0, 0.0, 0.0);
   circle(0, 0, .15, .2, 0, 10, 0);
   glPopMatrix();

   // Display the menu text
   glColor3f(0.0, 0.0, 0.0);
   glRasterPos3f(-b + .05 + .7, a - .53 - .35, .3);
   for (i=0; i < strlen(styleText1); i++)
   {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, styleText1[i]);
   }
   glRasterPos3f(-b + .05 + .8, a - .53 - 1.05, .3);
   for (i=0; i < strlen(styleText2); i++)
   {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, styleText2[i]);
   }
   glRasterPos3f(-b + .05 + .86, a - .53 - 1.75, .3);
   for (i=0; i < strlen(styleText3); i++)
   {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, styleText3[i]);
   }
}


void greetingMenu()
{
   char styleText1[] = {"Style 1"};
   char styleText2[] = {"Style 2"};
   char styleText3[] = {"Style 3"};

   glBegin(GL_QUADS);
   glColor3f(1, 1, 1);
   glVertex3f(-b + .04 + 2.1, a - .53, .18);
   glVertex3f(-b + 2.01 + 2.1, a - .53, .18);
   glVertex3f(-b + 2.01 + 2.1, a - .53 - 2.1, .18);
   glVertex3f(-b + .04 + 2.1, a - .53 - 2.1, .18);
   glEnd();

   glColor4f(.6, .6, .6, .7);
   glBegin(GL_LINES);
   glVertex3f(-b + 2.01 + 2.1, a - .53 - .7, .18);
   glVertex3f(-b + .04 + 2.1, a - .53 - .7, .18);

   glVertex3f(-b + 2.01 + 2.1, a - .53 - 1.4, .18);
   glVertex3f(-b + .04 + 2.1, a - .53 - 1.4, .18);
   glEnd();

   // Icons
   glPushMatrix();
   glTranslatef(-b + .04 + .15 + 2.1, a - .53 - .35, .18);
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_QUADS);
   glVertex3f(0, 0, .3);
   glVertex3f(0, .4, .3);
   glVertex3f(.2, .5, .3);
   glVertex3f(.2, .1, .3);

   glVertex3f(.2, .5, .3);
   glVertex3f(.2, .1, .3);
   glVertex3f(.4, 0, .3);
   glVertex3f(.4, .4, .3);
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-b + .04 + .15 + 2.1 + .4, a - .53 - .95, .18);
   glRotatef(90, 0, 0, 1);
   glTranslatef(-.08, 0, 0);
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_QUADS);
   glVertex3f(0, 0, .3);
   glVertex3f(0, .4, .3);
   glVertex3f(.2, .5, .3);
   glVertex3f(.2, .1, .3);

   glVertex3f(.2, .5, .3);
   glVertex3f(.2, .1, .3);
   glVertex3f(.4, 0, .3);
   glVertex3f(.4, .4, .3);
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-b + .04 + .25 + 2.1, a - .53 - 1.72, .18);
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_QUADS);
   glVertex3f(0, 0, .3);
   glVertex3f(0, .5, .3);
   glVertex3f(.2, .5, .3);
   glVertex3f(.2, 0, .3);
   glEnd();
   glPopMatrix();

   // Display menu text
   glColor3f(0.0, 0.0, 0.0);
   glRasterPos3f(-b + .05 + .7 + 2.1, a - .53 - .35, .3);
   for (i=0; i < strlen(styleText1); i++)
   {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, styleText1[i]);
   }
   glRasterPos3f(-b + .05 + .7 + 2.1, a - .53 - 1.05, .3);
   for (i=0; i < strlen(styleText2); i++)
   {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, styleText2[i]);
   }
   glRasterPos3f(-b + .05 + .7 + 2.1, a - .53 - 1.75, .3);
   for (i=0; i < strlen(styleText3); i++)
   {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, styleText3[i]);
   }
}


void greetingCardStyle()
{
   int i;
   // Greeting card
   glPushMatrix();
   glTranslatef(0,2,0);
   glScalef(cardOpen,1,1);

   // Card background
   glBegin(GL_QUADS);
   glColor3f(135/255.,1/255.,169/255.);
   glVertex3f(-3,-3,2);
   glVertex3f(-3,3,2);
   glColor3f(51/255.,0/255.,68/255.);
   glVertex3f(0, 4, 2);
   glVertex3f(0, -2, 2);

   glColor3f(51/255.,0/255.,68/255.);
   glVertex3f(0, 4, 2);
   glVertex3f(0, -2, 2);
   glColor3f(135/255.,1/255.,169/255.);
   glVertex3f(3,-3,2);
   glVertex3f(3, 3, 2);
   glEnd();

   // Border line pattern
   glColor4f(228/255.,255/255.,0/255.,1);
   if(flicker % 10 > 5)
       glColor4f(252/255.,168/255.,0/255., 1);
   glLineStipple(10, 0xAAAA);
   glEnable(GL_LINE_STIPPLE);
   glBegin(GL_LINE_LOOP);
   glVertex3f(-2.9, -2.8, 2.1);
   glVertex3f(-2.9, 3, 2.1);
   glVertex3f(0, 4, 2.1);
   glVertex3f(2.9, 3, 2.1);
   glVertex3f(2.9, -2.8, 2.1);
   glVertex3f(0, -1.8, 2.1);
   glEnd();
   glDisable(GL_LINE_STIPPLE);

   // Divider line
   glColor3f(42/255.,1/255.,55/255.);
   glLineWidth(2);
   glBegin(GL_LINES);
   glVertex3f(0,4,2.01);
   glVertex3f(0, -2, 2.01);
   glEnd();
   glPopMatrix();

   // Lamp
   glColor4f(239/255.,137/255.,0,cardOpen);
   glPushMatrix();
   glScalef(cardOpen,1,1);
   circle(-1.5,2,.6,1,1.35,4.55,0);

   glColor4f(1,1,1,cardOpen);
   circle(-1.5,2.89,.1,.8,1,8,1);

   glPushMatrix();
   glRotatef(18,0,0,1);
   glTranslatef(.72,.44,.1);
   glColor4f(182/255.,104/255.,0,cardOpen);
   circle(-1.5,2,.63,.15,1.35,10,0);
   glPopMatrix();

   if(cardOpen> 1)
   {
       glColor3f(0,0,0);
       glBegin(GL_TRIANGLES);
       glVertex3f(-1.5,2.18,2.5);
       glVertex3f(-1.52,2.64,2.5);
       glVertex3f(-1.45,2.18,2.5);
       glEnd();
   }

   // Blinking Pattern in the middle
   glPushMatrix();
   glScalef(cardOpen/7., 1/6., 1);
   glTranslatef(0, 5, 0);
   glLineWidth(2);
   for(i=0; i<30; i+=2)
   {
       arc(0,.5 + i,.75,.75,1.35,5,1);
       arc(0,-.5 + i,.75,.75,4.35,8,1);
   }

   glPopMatrix();

   glPopMatrix();

   if(cardOpen<1)
       cardOpen += .007;

   flicker ++;
}


void greetingCardStyle1()
{
   int i;
   // Greeting card
   glPushMatrix();
   glTranslatef(0,2,0);
   glScalef(cardOpen,1,1);

   // Card background
   glBegin(GL_QUADS);
   glColor3f(135/255.,1/255.,169/255.);
   glVertex3f(-3,-3,2);
   glVertex3f(-3,3,2);
   glColor3f(51/255.,0/255.,68/255.);
   glVertex3f(0, 4, 2);
   glVertex3f(0, -2, 2);

   glColor3f(185/255.,105/255.,68/255.);
   glVertex3f(-.5,-.5,2.2);
   glVertex3f(-.5,0.3,2.2);
   glVertex3f(.5, 0.3, 2.2);
   glVertex3f(.5, -.5, 2.2);

   glVertex3f(-.5,-.5+3,2.2);
   glVertex3f(-.5,.5+3.2,2.2);
   glVertex3f(.5, .5+3.2, 2.2);
   glVertex3f(.5, -.5+3, 2.2);

   glEnd();

   glEnable( GL_TEXTURE_2D );
   glBindTexture( GL_TEXTURE_2D, card1 ); //bind our texture to our shape

   glColor3f(1,1,1);
   glBegin (GL_QUADS);
   // glColor3f(51/255.,0/255.,68/255.);
   glTexCoord2d(0,0.0); glVertex3f(0, -2, 2);  //with our vertices we have to assign a texcoord
   glTexCoord2d(.25,0.0);  glVertex3f(3,-3,2); //so that our texture has some points to draw to
   // glColor3f(135/255.,1/255.,169/255.);
   glTexCoord2d(.25,.25); glVertex3f(3, 3, 2);
   glTexCoord2d(0,.25); glVertex3f(0, 4, 2);
   glEnd();
   glDisable( GL_TEXTURE_2D );

   // Border line pattern
   glColor4f(228/255.,255/255.,0/255.,1);
   if(flicker % 10 > 5)
       glColor4f(252/255.,168/255.,0/255., 1);
   glLineStipple(10, 0xAAAA);
   glEnable(GL_LINE_STIPPLE);
   glBegin(GL_LINE_LOOP);
   glVertex3f(-2.9, -2.8, 2.1);
   glVertex3f(-2.9, 3, 2.1);
   glVertex3f(0, 4, 2.1);
   glVertex3f(2.9, 3, 2.1);
   glVertex3f(2.9, -2.8, 2.1);
   glVertex3f(0, -1.8, 2.1);
   glEnd();
   glDisable(GL_LINE_STIPPLE);

   glColor3f(42/255.,1/255.,55/255.);
   glLineWidth(2);
   glBegin(GL_LINES);
   glVertex3f(0,4,2.01);
   glVertex3f(0, -2, 2.01);
   glEnd();
   glPopMatrix();

   glColor4f(239/255.,137/255.,0,cardOpen);
   glPushMatrix();
   glScalef(cardOpen,1,1);
   circle(-1.5,2,.6,1,1.35,4.55,0);

   glColor4f(1,1,1,cardOpen);
   circle(-1.5,2.89,.1,.8,1,8,1);

   glPushMatrix();
   glRotatef(18,0,0,1);
   glTranslatef(.72,.44,.1);
   glColor4f(182/255.,104/255.,0,cardOpen);
   circle(-1.5,2,.63,.15,1.35,10,0);
   glPopMatrix();

   if(cardOpen> 1)
   {
       glColor3f(0,0,0);
       glBegin(GL_TRIANGLES);
       glVertex3f(-1.5,2.18,2.5);
       glVertex3f(-1.52,2.64,2.5);
       glVertex3f(-1.45,2.18,2.5);
       glEnd();
   }

   // Blinking Pattern in the middle
   glPushMatrix();
   glScalef(cardOpen/7., 1/6., 1);
   glTranslatef(0, 5, 0);
   glLineWidth(2);
   for(i=0; i<30; i+=2)
   {
       arc(0,.5 + i,.75,.75,1.35,5,1);
       arc(0,-.5 + i,.75,.75,4.35,8,1);
   }

   glPopMatrix();

   if(cardOpen<1)
       cardOpen += .007;

   if(cardOpen>=1)
   {
       glColor3f(1,1,1);
       glRasterPos3f(-5,-4, 0);
       for (i=0; i < strlen(msg); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, msg[i]);
       }

       glRasterPos3f(-5,-4.5, 0);

       for ( i=0; i < strlen(msg1); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, msg1[i]);
       }

       glRasterPos3f(-.3,5+.5, 2.29);

       for ( i=0; i < strlen(input); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, input[i]);
       }

       glRasterPos3f(-.3,2, 2.29);

       for ( i=0; i < strlen(from); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, from[i]);
       }

       glRasterPos3f(-.3,1.7, 2.29);

       for ( i=0; i < strlen(name); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
       }

   }
   flicker ++;
}


void greetingCardStyle2()
{
   glEnable( GL_TEXTURE_2D );
   int i;
   glColor3f(1,1,1);
   // Greeting card
   glPushMatrix();
   glTranslatef(0,2,0);
   glScalef(1,cardOpen,1);

   // Card background
   glBindTexture( GL_TEXTURE_2D, card1 );

   glBegin(GL_QUADS);

   glTexCoord2d(0.25,0.0); glVertex3f(-3,0,2);
   glTexCoord2d(.5,0.0); glVertex3f(3,0,2);
   glTexCoord2d(.5,.25); glVertex3f(2.5, 4, 2);
   glTexCoord2d(0.25,0.25); glVertex3f(-2.5, 4, 2);

   glVertex3f(-2.4, 4, 2);
   glVertex3f(-1.75, 4, 2);
   glVertex3f(-1.9, 4.25, 2);
   glVertex3f(-2.25, 4.25, 2);

   glTexCoord2d(0,0.25); glVertex3f(-3, 0, 2);
   glTexCoord2d(.25,0.25); glVertex3f(3,0,2);
   glTexCoord2d(.25,.5); glVertex3f(3.7,-3, 2);
   glTexCoord2d(0.0,.5); glVertex3f(-3.7, -3, 2);
   glEnd();

   glDisable( GL_TEXTURE_2D );

   glColor3f(42/255.,1/255.,55/255.);
   glLineWidth(2);
   glBegin(GL_LINES);
   glVertex3f(-3,0,2.01);
   glVertex3f(3, 0, 2.01);
   glEnd();
   glPopMatrix();

   if(cardOpen>=1)
   {
       glColor3f(1,1,1);
       glRasterPos3f(-5,-4, 0);
       for (i=0; i < strlen(msg); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, msg[i]);
       }

       glRasterPos3f(-5,-4.5, 0);

       for ( i=0; i < strlen(msg1); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, msg1[i]);
       }

       glRasterPos3f(-2.4,5.5, 2.2);

       for ( i=0; i < strlen(input); i++)
       {

           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, input[i]);
       }

       glRasterPos3f(-2.43,-.2, 2.2);

       for ( i=0; i < strlen(from); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, from[i]);
       }

       glRasterPos3f(-2.43,-.5, 2.2);

       for ( i=0; i < strlen(name); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
       }

   }
   glPopMatrix();
   // Blinking Pattern in the middle
   if(cardOpen<1)
       cardOpen += .007;
}


void greetingCardStyle3()
{
   glEnable( GL_TEXTURE_2D );
   int i;
   glColor3f(1,1,1);
   // Greeting card
   glPushMatrix();
   glTranslatef(0,2,0);
   glScalef(1,cardOpen,1);

   // Card background
   glBindTexture( GL_TEXTURE_2D, card1 );

   glBegin(GL_QUADS);
   glTexCoord2d(.25,.25); glVertex3f(-2, 4, 2);
   glTexCoord2d(.5,.25);  glVertex3f(2,4,2);

   glTexCoord2d(.5,.5); glVertex3f(2,-4, 2);
   glTexCoord2d(.25,.5); glVertex3f(-2, -4, 2);
   glEnd();
   glDisable( GL_TEXTURE_2D );

   glColor3f(0,0,0);
   circle(2.1,1.7,.3,5,1,10,0);
   glPopMatrix();

   // Blinking Pattern in the middle
   glPopMatrix();

   if(cardOpen<1)
       cardOpen += .007;
   else
   {
       glColor3f(1,1,1);
       glRasterPos3f(-5,-4, 0);
       for (i=0; i < strlen(msg); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, msg[i]);
       }

       glRasterPos3f(-5,-4.5, 0);

       for ( i=0; i < strlen(msg1); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, msg1[i]);
       }

       glRasterPos3f(-1.7,4, 2.2);
       for (i=0; i < strlen(input); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, input[i]);
       }

       glRasterPos3f(-1.7, 0, 2.2);
       for (i=0; i < strlen(from); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, from[i]);
       }

       glRasterPos3f(-1.7,-.5, 2.2);
       for (i=0; i < strlen(name); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
       }
   }
}


void crackerStyle1()
{
   float k;

   glPushMatrix();
   for(k=-.09; k<=.09; k+=.01)
   {
       if(k!=-.04 && k!=.07)
       {
           glRotatef(particlesRotate, 0, 2, 0);
           anar_particles(k);
       }
   }
   glPopMatrix();
   particlesRotate++;
}


void crackerStyle2()
{
   glEnable( GL_TEXTURE_2D );
   int i;

   // Greeting card
   glPushMatrix();
   if(rocket == 1 && 1-cardOpen/2 > .05)
   {
       glTranslatef(0,2*cardOpen,0);
   }
      // Card background
   else
      glTranslatef(0,-10,0);

   glBindTexture( GL_TEXTURE_2D, card1 );

   glColor4f(1,1,1,1-cardOpen/2);
   glBegin(GL_QUADS);
   glTexCoord2d(0.75,0.25);
   glVertex3f(-1.5,-2,2);
   glTexCoord2d(1,0.25);
   glVertex3f(1.5,-2,2);
   glTexCoord2d(1,1);
   glVertex3f(1.5, -13, 2);
   glTexCoord2d(0.75,1);
   glVertex3f(-1.5, -13, 2);
   glEnd();

   glColor4f(1,1,1,1);
   glBegin(GL_QUADS);
   glTexCoord2d(0.75,0.0);
   glVertex3f(-.75,2,2);
   glTexCoord2d(1,0.0);
   glVertex3f(.75,2,2);
   glTexCoord2d(1,.25);
   glVertex3f(.75, -2, 2);
   glTexCoord2d(0.75,0.25);
   glVertex3f(-.75, -2, 2);
   glEnd();
   glPopMatrix();

   glDisable(GL_TEXTURE_2D);
   glDisable(GL_LIGHTING);
   glColor4f(1., 0, 0, 1);
   glBegin(GL_QUADS);
   glVertex3f(-2, 4.5, 2.15);
   glVertex3f(-1.2, 4.5, 2.15);
   glVertex3f(-1.2, 4, 2.15);
   glVertex3f(-2, 4, 2.15);
   glEnd();
   glColor4f(1,1,1,1);
   glRasterPos3f(-1.7, 4.25, 2.25);
   for (i=0; i < strlen(blast); i++)
   {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, blast[i]);
   }

   if(rocket == 1)
   {
      cardOpen += .017;
   }
}


void boom()
{
   /* Place the camera */
   glPushMatrix();

   glTranslatef (0.0, 0.0, -1.0);
   glRotatef (cam_angle, 0.0, 1.0, 0.0);

   /* If no explosion, draw cube */

   if (fuel > 0)
   {
       glPushMatrix ();

       glDisable (GL_LIGHTING);
       glDisable (GL_DEPTH_TEST);

       glBegin (GL_POINTS);
       for (i = 0; i < NUM_PARTICLES; i++)
       {
           glColor3fv (particles[i].color);
           glVertex3fv (particles[i].position);
       }

       glEnd ();

       glPopMatrix ();

       glEnable (GL_LIGHTING);
       glEnable (GL_LIGHT0);
       glEnable (GL_DEPTH_TEST);

       glNormal3f (0.0, 0.0, 1.0);

       for (i = 0; i < NUM_DEBRIS; i++)
       {
           glColor3fv (debris[i].color);

           glPushMatrix ();

           glTranslatef (debris[i].position[0],
                         debris[i].position[1],
                         debris[i].position[2]);

           glRotatef (debris[i].orientation[0], 1.0, 0.0, 0.0);
           glRotatef (debris[i].orientation[1], 0.0, 1.0, 0.0);
           glRotatef (debris[i].orientation[2], 0.0, 0.0, 1.0);

           glScalef (debris[i].scale[0],
                     debris[i].scale[1],
                     debris[i].scale[2]);

           glBegin (GL_TRIANGLES);
           glVertex3f (0.0, 0.5, 0.0);
           glVertex3f (-0.25, 0.0, 0.0);
           glVertex3f (0.25, 0.0, 0.0);
           glEnd ();

           glPopMatrix ();
       }
   }
   glPopMatrix();
   func();
   glDisable (GL_LIGHTING);
}


void crackerStyle3()
{
   // Bomb - cracker style 3
   float bomb_diffuse[] = {0, 204/255., 0, 0.8};
   float bomb_amb[] = {0, .5, 0, 1.};
   float bomb_spec[] = {0, .1, 0, 0};
   float diffuse[] = {0, 102/255., 51/255., 1.};
   float amb[] = {0, .1, 0, 1.};

   if(match < 1.5)
   {
       glLineWidth(2);
       glEnable(GL_LIGHTING);
       glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
       glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
       glutWireSphere(.52, 66, 5);
       glMaterialfv(GL_FRONT, GL_DIFFUSE, bomb_diffuse);
       glMaterialfv(GL_FRONT, GL_AMBIENT, bomb_amb);
       glMaterialfv(GL_FRONT, GL_SPECULAR, bomb_spec);
       glutSolidSphere(.48, 20, 56);
       glDisable(GL_LIGHTING);
       arc(0, 3, .05, .4, 0, 2, 1);
   }

   if(match < 1.5)
   {
       glPushMatrix();
       if(blow == 1)
       {
           glTranslatef(0, -match, 0);
           match += .01;
       }
       if(match < 1.2)
       {
           // Matchstick
           glColor4f(1,1,1,1);
           glBegin(GL_LINES);
           glVertex3f(-1, 4.5, 2.15);
           glVertex3f(0, 4.5, 2.15);
           glEnd();
           glColor4f(1,0,0,.5);
           circle(0, 4.5, .05, .15, 1, 8, 0);
       }
       glColor4f(1., 153/255., 0, 1);
       circle(0, 4.7, .1,.5,1,8,1);
       glPopMatrix();

       glColor4f(1., 0, 0, 1);
       glBegin(GL_QUADS);
       glVertex3f(-2, 4.5, 2.15);
       glVertex3f(-1.2, 4.5, 2.15);
       glVertex3f(-1.2, 4, 2.15);
       glVertex3f(-2, 4, 2.15);
       glEnd();

       glColor4f(1,1,1,1);
       glRasterPos3f(-1.7, 4.25, 2.25);
       for (i=0; i < strlen(blast); i++)
       {
           glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, blast[i]);
       }
   }
   else
       boom();
}


void welcome()
{
   glDisable(GL_LIGHTING);
   glEnable(GL_TEXTURE_2D);

   glBindTexture( GL_TEXTURE_2D, card1 );

   glColor3f(1,1,1);
   glBegin(GL_QUADS);
   if(inc%25>12)
   {
       glTexCoord2d(0,.5); glVertex3f(-3, 6, 2);  //with our vertices we have to assign a texcoord
       glTexCoord2d(.25,.5); glVertex3f(3,6,2); //so that our texture has some points to draw to
       glTexCoord2d(.25,1);  glVertex3f(3,-3, 2);
       glTexCoord2d(0,1); glVertex3f(-3, -3, 2);
       glEnd();
   }
   else
   {
       glTexCoord2d(.25,.5); glVertex3f(-3, 6, 2);  //with our vertices we have to assign a texcoord
       glTexCoord2d(.5,.5); glVertex3f(3,6,2); //so that our texture has some points to draw to
       glTexCoord2d(.5,1);  glVertex3f(3,-3, 2);
       glTexCoord2d(0.25,1); glVertex3f(-3, -3, 2);
       glEnd();
   }
   inc++;

   glDisable(GL_TEXTURE_2D);
}


void display(void)
{
   int i;
   float j, k;
   glEnable(GL_BLEND); // Enable the OpenGL Blending functionality
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glClearColor(0, 0, 0, 1); // Clear the background of our window to white
   glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); // Load the Identity Matrix to reset our locations
   gluLookAt(0, 1, 1, 0, 0, 0, 0, 1, 0);

   // Menu
   glBegin(GL_QUADS);

   // Background bar
   glColor4f(.6, .6, .6, menuHover);
   glVertex3f(-b, a, .15);
   glVertex3f(b, a, .15);
   glVertex3f(b, a - .6, .15);
   glVertex3f(-b, a - .6, .15);

   // Cracker menu
   glColor4f(1, .7, .7, 1);
   glVertex3f(-b + .05, a - .05, .2);
   glVertex3f(-b + 2, a - .05, .2);
   glVertex3f(-b + 2, a - .5, .2);
   glVertex3f(-b + .05, a - .5, .2);

   glColor3f(1, .3, .3);
   glVertex3f(-b + .04, a - .043, .18);
   glVertex3f(-b + 2.01, a - .043, .18);
   glVertex3f(-b + 2.01, a - .53, .18);
   glVertex3f(-b + .04, a - .53, .18);

   // Greeting card menu
   glColor3f(.7, 1, .7);
   // glColor3f(40/255., 255/255., 22/255.);
   glVertex3f(-b + .05 + 2.1, a - .05, .2);
   glVertex3f(-b + 2 + 2.1, a - .05, .2);
   glVertex3f(-b + 2 + 2.1, a - .5, .2);
   glVertex3f(-b + .05 + 2.1, a - .5, .2);

   glColor3f(.1, 1, .1);
   glVertex3f(-b + .04 + 2.1, a - .043, .18);
   glVertex3f(-b + 2.01 + 2.1, a - .043, .18);
   glVertex3f(-b + 2.01 + 2.1, a - .53, .18);
   glVertex3f(-b + .04 + 2.1, a - .53, .18);
   glEnd();

   // Display Menubar Text
   glColor3f(0.0, 0.0, 0.0);
   glRasterPos3f(-b + .05 + .7, a - .25, .3);

   for (i=0; i < strlen(crackerText); i++)
   {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, crackerText[i]);
   }
   glRasterPos3f(-b + .05 +.009 + .7, a +.009 - .25, .3);
   for (i=0; i < strlen(crackerText); i++)
   {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, crackerText[i]);
   }

   glColor3f(0.0, 0.0, 0.0);
   glRasterPos3f(-b + .05 + 2.65, a - .25, .3);
   for (i=0; i < strlen(greetingText); i++)
   {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, greetingText[i]);
   }
   glRasterPos3f(-b + .05 +.009 + 2.65, a +.009 - .25, .3);
   for (i=0; i < strlen(greetingText); i++)
   {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, greetingText[i]);
   }

   glDisable(GL_LIGHTING);

   if(cracker == 1)
       crackerMenu();
   if(greeting == 1)
       greetingMenu();

   if(crackerSubMenu[0] == 1)
   {
       glEnable(GL_LIGHTING);
       // Anar
       glPushMatrix();
       cylinder();
       glShadeModel (GL_SMOOTH);
       glTranslatef(-1.0, -1.0, 0.0);
       glCallList(startList);
       glPopMatrix();
       // Particles
       crackerStyle1();
       glDisable(GL_LIGHTING);
   }
   else if(crackerSubMenu[1] == 1)
   {
       crackerStyle2();
       if(1-cardOpen/2 < .05)
       {
           boom();
       }
   }
   else if(crackerSubMenu[2] == 1)
   {
       crackerStyle3();
   }
   else if(greetingSubMenu[0] == 1)
       greetingCardStyle1();
   else if(greetingSubMenu[1] == 1)
       greetingCardStyle2();
   else if(greetingSubMenu[2] == 1)
       greetingCardStyle3();
   // else welcome();

   flicker++;

   glutSwapBuffers();
   glFlush();
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize(1000, 1000);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);

   srand (time (NULL));
   myinit();
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable( GL_BLEND );

   glutDisplayFunc(display);
   glutIdleFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouseClicks);
   glutPassiveMotionFunc(mouseMotion);
   card1 = LoadTexture( "texture.raw", 1024, 1024 );

   glEnable (GL_LIGHT0);
   glEnable (GL_LIGHT1);
   glLightfv (GL_LIGHT0, GL_AMBIENT, light0Amb);
   glLightfv (GL_LIGHT0, GL_DIFFUSE, light0Dif);
   glLightfv (GL_LIGHT0, GL_SPECULAR, light0Spec);
   glLightfv (GL_LIGHT0, GL_POSITION, light0Pos);
   glLightfv (GL_LIGHT1, GL_AMBIENT, light1Amb);
   glLightfv (GL_LIGHT1, GL_DIFFUSE, light1Dif);
   glLightfv (GL_LIGHT1, GL_SPECULAR, light1Spec);
   glLightfv (GL_LIGHT1, GL_POSITION, light1Pos);
   glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
   glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, materialAmb);
   glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, materialDif);
   glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, materialSpec);
   glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);
   glEnable (GL_NORMALIZE);

   glutMainLoop ();

   //Free our texture
   FreeTexture( card1 );
   return 0;
}
