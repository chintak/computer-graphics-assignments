#include <GLUT/glut.h>
#include <math.h>
#define b 750
#define a 500
#define PI 3.1415926535898
int rain = 0, cloud[5], i, move=0;


void myinit(void)
{
    glClearColor(0.8, 0.8, 0.8, 0.0); /* gray background */

    glMatrixMode(GL_PROJECTION);      /* In World coordinates: */
    glLoadIdentity();                 /* position the "clipping rectangle" */
    gluOrtho2D( -b, b, -a, a);/* at -B/2, its right edge at +B/2, its bottom */
    glMatrixMode(GL_MODELVIEW);       /* edge at -B/2 and its top edge at +B/2 */
}


void circle(int x1, int y1, int radiusx,int radiusy, int result, int flag)
{   float x2,y2;
    float angle;

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glPointSize(radiusx);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1,y1);

    for (angle=1.0f;angle<result;angle+=.05)
    {
        if(flag == 1)
            glColor3f(114/255., 187/255., 10/255.);
        x2 = x1+sin(angle)*radiusx;
        y2 = y1+cos(angle)*radiusy;
        glVertex2f(x2,y2);
    }

    glEnd();
}

int draw_half_cloud(int x,int y,int radius)
{
    int i;
    int d=radius;
    int ans=x;

    glPushMatrix();
    circle(x,y,radius,radius,10, 0);
    for(i=1; i<3; i++)
    {
        glTranslatef(d*(i*0.6+1),d, 0);
        circle(x,y,radius*(i*0.4+1),radius*(i*0.4+1),10, 0);
        circle(x,y-30*(1+i*0.5),radius*(i*0.4+1),radius*(i*0.4+1),10, 0);

        ans=ans+d*(i*.6+1);
    }
    glPopMatrix();

    return ans;
}


void draw_full_cloud(int x,int y)
{
    int ans;

    glPushMatrix();
    ans = draw_half_cloud(x, y, 20);
    glRotatef(180,0,1,0);
    glTranslatef(-2*ans,0,0);
    ans =draw_half_cloud(x, y, 20);
    glPopMatrix();
}


void draw_fence(void)
{
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_QUADS);
    glColor3f ( 203/255., 139/255., 14/255.);
    glVertex2i(-b + 35, -25);
    glVertex2i(-b + 35, 85);
    glColor3f ( 140/255., 94/255., 4/255.);
    glVertex2i(-b + 50, 80);
    glVertex2i(-b + 50, -20);
    glEnd();
}


void leg(void)
{
    glColor3f (246/255., 228/255., 177/255.);
    glBegin(GL_QUADS);
    /* leg*/
    glVertex2i(0,-80);
    glVertex2i(20,-80);
    glVertex2i(20,-180);
    glVertex2i(0,-180);

    glEnd();
    glColor3f (224/255., 0/255., 206/255.);
    circle(12,-170,20,12,10, 0); //shoes
}


void draw_flower(void)
{
    glPushMatrix();
    glScalef(.1, .08, 0);
    glColor3f ( 1, 1, 0);
    draw_full_cloud(0,0);
    glPopMatrix();
    glColor3f ( 0, 0, 0);
    circle(7, 0, 3, 3, 10, 0);
}


void animate(void)
{
    move += 1;

    rain += 1;
    rain %= 1500;

    for(i=0; i<5; i++)
    {
        cloud[i] += 1;
        cloud[i] %= 1500+500*i;
    }
    glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(animate);
            break;
        default:
        break;
    }
}


void draw_grass(void)
{
    glBegin(GL_TRIANGLES);
    glColor3f ( 20/255., 83/255., 1/255.);
    glVertex2i(0, 0);
    glVertex2i(5, 30);
    glVertex2i(10, 0);
    glVertex2i(10, 0);
    glVertex2i(13, 20);
    glVertex2i(20, 0);
    glVertex2i(20, 0);
    glVertex2i(27, 36);
    glVertex2i(30, 0);
    glVertex2i(30, 0);
    glVertex2i(43, 30);
    glVertex2i(38, 0);
    glEnd();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);     /*clear the window */

    glMatrixMode(GL_MODELVIEW);       /* The following coordinates are expressed */
    glLoadIdentity();                 /* in terms of World coordinates */
    int j;

    glEnable(GL_POINT_SMOOTH);

    // Sky Gradient
    glBegin(GL_QUADS);
    glColor3f(159/255., 231/255., 239/255.);
    glVertex2i(-b, 0);
    glVertex2i(b, 0);
    glColor3f(96/255., 198/255., 210/255.);
    glVertex2i(b, a/2);
    glVertex2i(-b, a/2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(7/255., 159/255., 177/255.);
    glVertex2i(-b, a);
    glVertex2i(b, a);
    glColor3f(96/255., 198/255., 210/255.);
    glVertex2i(b, a/2);
    glVertex2i(-b, a/2);
    glEnd();

    // Grass Gradient
    glBegin(GL_QUADS);
    glColor3f(55/255., 89/255., 4/255.);
    glVertex2i(-b, 0);
    glVertex2i(b, 0);
    glColor3f(114/255., 187/255., 10/255.);
    glVertex2i(b, -a/3);
    glVertex2i(-b, -a/3);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(140/255., 203/255., 49/255.);
    glVertex2i(-b, -a);
    glVertex2i(b, -a);
    glColor3f(114/255., 187/255., 10/255.);
    glVertex2i(b, -a/3);
    glVertex2i(-b, -a/3);
    glEnd();

    // Grass, behind the fence
    glPushMatrix();
    glTranslatef(-b, 0, 0);
    for(i=0; i<40; i++)
    {
        draw_grass();
        glTranslatef(40, 0, 0);
    }
    glPopMatrix();

    // Fence
    glBegin(GL_QUADS);
    glColor3f ( 203/255., 139/255., 14/255.);
    glVertex2i(-b, 5);
    glVertex2i(b, 5);
    glColor3f ( 140/255., 94/255., 4/255.);
    glVertex2i(b, -10);
    glVertex2i(-b, -10);

    glColor3f ( 203/255., 139/255., 14/255.);
    glVertex2i(-b, 75);
    glVertex2i(b, 75);
    glColor3f ( 140/255., 94/255., 4/255.);
    glVertex2i(b, 60);
    glVertex2i(-b, 60);
    glEnd();

    glPushMatrix();
    for(i=0; i<30; i++)
    {
        draw_fence();
        glTranslatef(60, 0, 0);
    }
    glPopMatrix();

    // Flowers
    glPushMatrix();
    glTranslatef(-b,-30,0);
    draw_flower();
    glPushMatrix();
    for (i=0; i<10; i++)
    {
        glTranslatef(150,0,0);
        draw_flower();
    }
    glPopMatrix();

    glTranslatef(70,-5,0);
    for (i=0; i<10; i++)
    {
        glTranslatef(150,0,0);
        draw_flower();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-b/2-120, -50, 0);

    // Roof
    glBegin(GL_POLYGON);
    glColor3f ( 189/255., 74/255., 5/255.);
    glVertex2i(-60, 150);
    glVertex2i(-30, 200);
    glVertex2i(340, 200);
    glVertex2i(370, 150);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f ( 138/255., 54/255., 4/255.);
    for (j=0; j<5; j++)
    {
        glVertex2i(-53 + 7*j, 160 + 10*j);
        glVertex2i(363 - 7*j, 160+ 10*j);
    }
    glEnd();

    // Chimney
    glPushMatrix();
    glScalef(.3, .3, 0);

    glColor3f ( 160/255., 160/255., 160/255.);
    glTranslatef(0, (rain % 100)*10, 0);
    draw_full_cloud(900,800);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f ( 189/255., 76/255., 8/255.);
    glVertex2i(280, 220);
    glVertex2i(280, 180);
    glColor3f ( 118/255., 47/255., 4/255.);
    glVertex2i(310, 180);
    glVertex2i(310, 220);
    glEnd();

    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f ( 0,0,0);
    glVertex2i(275, 220);
    glVertex2i(315, 220);
    glEnd();

    // House
    glBegin(GL_POLYGON);
    glColor3f ( 249/255., 209/255., 22/255.);
    glVertex2i(-50, 0);
    glVertex2i(150, 0);
    glVertex2i(150, 150);
    glVertex2i(50, 200);
    glVertex2i(-50, 150);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f ( 217/255., 184/255., 28/255.);
    glVertex2i(150, 20);
    glVertex2i(350, 20);
    glVertex2i(350, 150);
    glVertex2i(150, 150);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f ( 189/255., 74/255., 5/255.);
    glVertex2i(-50, 0);
    glVertex2i(150, 0);
    glVertex2i(150, 10);
    glVertex2i(-50, 10);
    glVertex2i(150, 20);
    glVertex2i(350, 20);
    glVertex2i(350, 30);
    glVertex2i(150, 30);
    glEnd();

    // Roof Border
    glLineWidth(10);
    glBegin(GL_LINE_STRIP);
    glColor3f ( 102/255., 51/255., 0/255.);
    glVertex2i(-60, 150);
    glVertex2i(50, 200);
    glVertex2i(160, 150);
    glVertex2i(370, 150);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f ( 142/255., 51/255., 0/255.);
    glVertex2i(160, 150);
    glVertex2i(370, 150);
    glEnd();

    // Door
    glBegin(GL_QUADS);
    glColor3f ( 102/255., 51/255., 0/255.);
    glVertex2i(215, 20);
    glVertex2i(215, 105);
    glVertex2i(285, 105);
    glVertex2i(285, 20);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f ( 153/255., 102/255., 0/255.);
    glVertex2i(220, 20);
    glVertex2i(280, 20);
    glVertex2i(280, 100);
    glVertex2i(220, 100);
    glEnd();

    // Window
    glBegin(GL_QUADS);
    glColor3f ( 102/255., 51/255., 0/255.);
    glVertex2i(-5, 110);
    glVertex2i(105, 110);
    glVertex2i(105, 40);
    glVertex2i(-5, 40);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f ( 153/255., 153/255., 153/255.);
    glVertex2i(0, 105);
    glVertex2i(100, 105);
    glVertex2i(100, 45);
    glVertex2i(0, 45);
    glEnd();
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f ( 80/255., 80/255., 80/255.);
    glVertex2i(50, 105);
    glVertex2i(50, 40);
    glVertex2i(100, 75);
    glVertex2i(0, 75);
    glEnd();
    glPopMatrix();

    // Clouds
    glPushMatrix();
    glTranslatef(move, 0, 0);
    glColor3f(198/255., 202/255., 203/255.);
    glPushMatrix();
    glScalef(.9, .8, 0);
    draw_full_cloud(-b+20,a-125);
    glPopMatrix();
    draw_full_cloud(-a+60,a-100);
    glTranslatef(300,100,0);
    glScalef(1,.6,0);
    draw_full_cloud(-a+60,a-100);
    glTranslatef(400,-100,0);
    glScalef(1.2,1.6,0);
    draw_full_cloud(-a+60,a-100);
    glTranslatef(300,-100,0);
    glScalef(1.,1.,0);
    draw_full_cloud(-a+60,a-100);
    glPopMatrix();

    glColor3f(198/255., 202/255., 203/255.);
    glPushMatrix();
    glTranslatef((cloud[0]-b)%1500,-100,0);
    glScalef(1.,1.,0);
    draw_full_cloud(0,a-100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((cloud[1]-b-500)%1500,-80,0);
    glScalef(1.,1.,0);
    draw_full_cloud(0,a-100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((cloud[2]-b-1000)%1500,-40,0);
    glScalef(1.,1.,0);
    draw_full_cloud(0,a-100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((cloud[3]-b-1500)%1500,-20,0);
    glScalef(1.,1.,0);
    draw_full_cloud(0,a-100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((cloud[4]-b-2000)%1500,0,0);
    glScalef(1.,1.,0);
    draw_full_cloud(0,a-100);
    glPopMatrix();

    // Tree
    glPushMatrix();
    glColor3f ( 0, 1, 0.0);
    glScalef(1.5,2.4,0);
    glTranslatef(0,120,0);
    draw_full_cloud(0,0);
    glTranslatef(35,0,0);
    draw_full_cloud(0,0);
    glPopMatrix();

    // Tree Trunk
    glColor3f ( 0.5f , .35f, .05f);
    glBegin(GL_QUADS);
    glVertex2i(120, 250);
    glVertex2i(90, -100);
    glColor3f ( 100/255. , 61/255., 10/255.);
    glVertex2i(200, -100);
    glVertex2i(170, 250);
    glEnd();
    glColor3f ( 0, 1, 0.0);
    circle(145, 260, 50, 50, 10,0);

    // Road
    glBegin(GL_QUADS);
    glColor3f ( 100/255., 100/255., 100/255.);
    glVertex2i(-210, -30);
    glVertex2i(-280, -30);
    glColor3f ( 153/255., 153/255., 153/255.);
    glVertex2i(-320, -a);
    glVertex2i(-170, -a);
    glEnd();

    glPushMatrix();
    glColor3f (59/255., 212/255., 250/255.);
    if(rain%100 > 50)
        circle(330, -300, 90, 20, 10, 1);
    else
        circle(330, -300, 130, 60, 10, 1);
    glPopMatrix();

    glPushMatrix();
    if(rain%100 > 50)
        glTranslatef(0, 5, 0);
    else
        glTranslatef(0, -5, 0);
    glPushMatrix();
    glRotatef(150,0,0,1);
    glTranslatef(-300,-200,0);

    // Umbrella
    glColor3f ( 1,0,0);
    circle(100,-20,140,140,4.5,0);
    glRotatef(37,0,0,1);
    glTranslatef(-40,-80,0);
    glColor3f ( .5,0,0);
    circle(108,-13,140,30,10,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(320,-100,0);

    // Umbrella stick
    glLineWidth(5.);
    glBegin(GL_LINE_STRIP);
    glColor3f (0, 0, 0);
    glVertex2i(-30, 190);
    glVertex2i(-30, 90);
    glEnd();

    // Hands
    glColor3f (246/255., 228/255., 177/255.);
    circle(-30, 90, 10, 10, 10, 0);
    glLineWidth(14.);
    glBegin(GL_LINE_STRIP);
    glVertex2i(-30, 90);
    glVertex2i(-20, 20);
    glVertex2i(10, 80);
    glEnd();
    circle(-20, 20, 5, 5, 10,0);
    glLineWidth(14.);
    glBegin(GL_LINE_STRIP);
    glColor3f (246/255., 228/255., 177/255.);
    glVertex2i(70, 80);
    glVertex2i(110, 30);
    glVertex2i(70, 0);
    glEnd();
    circle(110, 30, 5, 5, 10,0);

    // Skirt
    glColor3f ( 49/255., 6/255., 71/255.);
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(80,0);
    glVertex2i(110,-80);
    glVertex2i(-30,-80);

    // Shirt
    glColor3f ( 156/255., 30/255., 222/255.);
    glVertex2i(0,0);
    glVertex2i(80,0);
    glVertex2i(80,80);
    glVertex2i(0,80);
    glEnd();

    glColor3f (246/255., 228/255., 177/255.);
    circle(40,80,18,18,10,0);

    glBegin(GL_QUADS);
    // Backdrop Hair
    glColor3f (0,0,0);
    glVertex2i(5, 80);
    glVertex2i(75, 80);
    glVertex2i(75, 120);
    glVertex2i(5, 120);

    // Neck
    glColor3f (246/255., 228/255., 177/255.);
    glVertex2i(25, 80);
    glVertex2i(55, 80);
    glVertex2i(55, 100);
    glVertex2i(25, 100);
    glEnd();

    glColor3f (0,0,0);

    // Hair
    circle(40,150,55,45,10,0);
    glColor3f (246/255., 228/255., 177/255.);

    // Head
    circle(40,130,45,35,10,0);

    glColor3f (0,0,0);

    // Eyes
    glPushMatrix();
    if(rain%100 > 50)
    {
        circle(23,135,3,3,10,0);
        circle(57,135,3,3,10,0);
    }
    else
    {
        circle(23,135,5,5,10,0);
        circle(57,135,5,5,10,0);
    }
    glPopMatrix();

    glPushMatrix();
    glRotatef(145,0,0,1);
    glTranslatef(0,-280,0);
    glColor3f (0,0,0);
    circle(40,120,10,10,4.5,0);

    // Lips
    glColor3f (246/255., 64/255., 192/255.);
    glRotatef(180,0,0,1);
    glTranslatef(-30,-164,0);
    circle(0,0,10,10,4.5,0);
    glPopMatrix();

    // Legs
    glPushMatrix();
    leg();
    glTranslatef(60,0,0);
    leg();
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    // Puddle
    glColor3f (59/255., 212/255., 250/255.);
    circle(30, -200, 100, 35, 10, 1);
    glColor3f (59/255., 212/255., 250/255.);
    circle(630, -240, 100, 35, 10, 1);
    glColor3f (59/255., 212/255., 250/255.);
    circle(-580, -180, 100, 35, 10, 1);
    glColor3f (59/255., 212/255., 250/255.);
    circle(-400, -250, 100, 35, 10, 1);

    // Rain
    for(i=1;i<12;i++)
    {
        for(j=0;j<12;j++)
        {
            glColor3f(21/255., 229/255., 255/255.);
            if (rain%20 > 10) {
                circle(-b+(i%2)*75 + j*150, a-100*i, 3,7,10,0);
            }
            else
                circle(-b+(i%2)*75 + j*150 - 75, a-100*i, 3,7,10,0);
        }
    }

    glutSwapBuffers();
    glFlush();                       /* send all commands */

}
