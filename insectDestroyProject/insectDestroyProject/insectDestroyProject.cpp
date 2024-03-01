/*********
   CTIS164 - Template Source Program
----------
STUDENT : Ece Tuðba Cebeci
SECTION : 004
HOMEWORK: 3 (Sad Death of Insects with poison drop of insect powder)
----------
PROBLEMS: Even if the space key is pressed, it sometimes gets stuck and doesn't work.
----------
ADDITIONAL FEATURES: ---
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1400
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  1000 // Period for the timer.
#define TIMER_ON         0 // 0:disable timer, 1:enable timer

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

int handX = -665, handY = 0; // my variable for movement of hand with spray

int insectPowderX = handX + 30, insectPowderY = handY + 13; // my variable for movement od the green insect powder
int insectX = 100, insectY = -297; // my variables for movement insect

int insectPowderSpeed = 10;
int insectSpeed = 2;

// these are my controlling tools
bool isContinueSpray = true;
bool isBulletFired = false;
bool bulletVisible = false;
bool targetHit = false;

int bulletAngle = 0; // Initalization of the ange of the insect pwder as a bullet


//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

void drawGradientRectangle()
{
    // to make the background blue with a gradient
    glBegin(GL_QUADS);
    glColor3ub(230, 234, 255); // starting color - light blue
    glVertex2f(-700, 400); // top left
    glColor3ub(83, 140, 193); // ending color - dark blue
    glVertex2f(700, 400); // top right
    glVertex2f(700, -400); // bottom right
    glVertex2f(-700, -400); // bottom left
    glEnd();
}

void displayScreen()
{
    glColor3ub(54, 54, 54);
    glRectf(-700, 400, 700, 250); // top rectangle

    glColor3ub(54, 54, 54);
    glRectf(-700, 250, -665, -320); // left rectangle

    glColor3ub(54, 54, 54);
    glRectf(650, 270, 700, -320); // right rectangle

    glColor3ub(54, 54, 54);
    glRectf(-700, -320, 700, -400); // bottom rectangle
}

void displayHand(int x, int y)
{
    // the numbers in the comment section below are the way I numbered the figure on the paper before writing it in the code.
    // I wrote it so that there is no confusion in my code and its coordinates.
    // you don't need to pay attention.

    // the part of the finger above the ring
    glColor3ub(244, 206, 142);
    glBegin(GL_QUADS);
    glVertex2f(x, y); //1
    glVertex2f(x + 4, y + 15); //3
    glVertex2f(x + 12, y + 9); //4
    glVertex2f(x + 10, y); //2
    glEnd();

    glColor3ub(244, 206, 142);
    glBegin(GL_QUADS);
    glVertex2f(x + 3, y + 15); //3
    glVertex2f(x + 12, y + 9); //4
    glVertex2f(x + 25, y + 22); //8
    glVertex2f(x + 20, y + 28); //7
    glEnd();

    // fingertip of above finger
    glColor3ub(244, 206, 142);
    circle(x + 23, y + 25, 3);

    // the part of the finger below the ring
    glColor3ub(244, 206, 142);
    glBegin(GL_QUADS);
    glVertex2f(x, y); //1
    glVertex2f(x + 10, y); //2
    glVertex2f(x + 5, y - 17); //10
    glVertex2f(x - 5, y - 17); //10*
    glEnd();

    glColor3ub(244, 206, 142);
    glBegin(GL_QUADS);
    glVertex2f(x - 5, y - 17); //10*
    glVertex2f(x + 5, y - 17); //10
    glVertex2f(x + 8, y - 22); //11
    glVertex2f(x - 5, y - 22); //11*
    glEnd();

    // the thumb
    glColor3ub(244, 206, 142);
    glBegin(GL_QUADS);
    glVertex2f(x + 8, y - 22); //11
    glVertex2f(x + 21, y - 22); //12
    glVertex2f(x + 25, y - 12); //20
    glVertex2f(x + 19, y - 7); //19
    glEnd();

    glColor3ub(244, 206, 142);
    glBegin(GL_QUADS);
    glVertex2f(x + 8, y - 22); //11
    glVertex2f(x + 21, y - 22); //12
    glVertex2f(x + 18, y - 35); //14
    glVertex2f(x + 11, y - 35); //13
    glEnd();

    glColor3ub(244, 206, 142);
    glBegin(GL_QUADS);
    glVertex2f(x + 11, y - 35); //13
    glVertex2f(x + 18, y - 35); //14
    glVertex2f(x + 15, y - 39); //16
    glVertex2f(x + 8, y - 39); //15
    glEnd();

    glColor3ub(244, 206, 142);
    glBegin(GL_QUADS);
    glVertex2f(x + 8, y - 39); //15
    glVertex2f(x + 15, y - 39); //16
    glVertex2f(x, y - 52); //18
    glVertex2f(x, y - 42); //17
    glEnd();

    // thumb tip
    glColor3ub(244, 206, 142);
    circle(x + 21, y - 11, 4);

    // the ring
    glColor3ub(47, 79, 79);
    glRectf(x + 6, y - 15, x - 3, y - 12);

    // finger-to-finger connection as there is space between two fingers
    glColor3ub(244, 206, 142);
    glBegin(GL_QUADS);
    glVertex2f(x - 5, y - 22); //11*
    glVertex2f(x + 21, y - 22); //12
    glVertex2f(x, y - 52); //18
    glVertex2f(x, y - 42); //17
    glEnd();

    glColor3ub(244, 206, 142);
    glBegin(GL_QUADS);
    glVertex2f(x + 8, y - 39); //15
    glVertex2f(x + 15, y - 39); //16
    glVertex2f(x + 8, y - 22); //11
    glVertex2f(x + 21, y - 22); //12
    glEnd();
}

void displaySpray(int x, int y)
{
    // the numbers or letters in the comment section below are the way I numbered the figure on the paper before writing it in the code.
    // I wrote it so that there is no confusion in my code and its coordinates.
    // you don't need to pay attention.

    // top of the spray bottle
    glColor3ub(238, 183, 45);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 25, y + 19); //A - top of triangle
    glVertex2f(x + 13, y - 5); //B sol
    glVertex2f(x + 35, y - 5); //C sað
    glEnd();

    // the apparatus from which the spray water comes out
    glColor3ub(105, 105, 105);
    glRectf(x + 20, y + 19, x + 30, y + 7);

    // frame of this apparatus
    glColor3ub(79, 79, 79);
    glBegin(GL_LINES);
    glVertex2f(x + 20, y + 19);
    glVertex2f(x + 20, y + 7);
    glEnd();

    glColor3ub(79, 79, 79);
    glBegin(GL_LINES);
    glVertex2f(x + 30, y + 7);
    glVertex2f(x + 20, y + 7);
    glEnd();

    glColor3ub(79, 79, 79);
    glBegin(GL_LINES);
    glVertex2f(x + 30, y + 7);
    glVertex2f(x + 30, y + 19);
    glEnd();

    // the middle of the spray bottle
    glColor3ub(238, 183, 45);
    glRectf(x + 13, y - 5, x + 35, y - 52);

    // the frame of this middle part
    glColor3ub(214, 166, 45);
    glBegin(GL_LINES);
    glVertex2f(x + 20, y + 7);
    glVertex2f(x + 13, y - 5);
    glEnd();

    glColor3ub(214, 166, 45);
    glBegin(GL_LINES);
    glVertex2f(x + 13, y - 5);
    glVertex2f(x + 13, y - 52);
    glEnd();

    glColor3ub(214, 166, 45);
    glBegin(GL_LINES);
    glVertex2f(x + 13, y - 52);
    glVertex2f(x + 35, y - 52);
    glEnd();

    glColor3ub(214, 166, 45);
    glBegin(GL_LINES);
    glVertex2f(x + 35, y - 52);
    glVertex2f(x + 35, y - 5);
    glEnd();

    glColor3ub(214, 166, 45);
    glBegin(GL_LINES);
    glVertex2f(x + 35, y - 5);
    glVertex2f(x + 30, y + 7);
    glEnd();

    // the hole where insecticide comes out
    glColor3ub(28, 28, 28);
    circle(x + 28, y + 13, 2);

    // the line in the middle-bottom of the spray bottle
    glColor3ub(205, 133, 63);
    glRectf(x + 13, y - 40, x + 35, y - 45);
}

void displayInsectPowder(int x, int y)
{
    // frame of the drop of insecticide
    glColor3ub(18, 125, 25);
    circle_wire(x + 25, y, 9);

    // the tip of a drop of insecticide
    glColor3ub(25, 162, 34);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y); //A - top of triangle
    glVertex2f(x + 25, y + 9); //B top
    glVertex2f(x + 25, y - 9); //C bottom
    glEnd();

    // the frame of the tip of a drop of insecticide
    glColor3ub(18, 125, 25);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x + 25, y + 9);
    glEnd();

    glColor3ub(18, 125, 25);
    glBegin(GL_LINES);
    glVertex2f(x + 25, y + 9);
    glVertex2f(x + 25, y - 5);
    glEnd();

    glColor3ub(18, 125, 25);
    glBegin(GL_LINES);
    glVertex2f(x + 25, y - 5);
    glVertex2f(x, y);
    glEnd();

    // the drop of insecticide
    glColor3ub(25, 162, 34);
    circle(x + 25, y, 9);
}

void displayInsect(int x, int y)
{
    // the numbers or letters in the comment section below are the way I numbered the figure on the paper before writing it in the code.
    // I wrote it so that there is no confusion in my code and its coordinates.
    // you don't need to pay attention.

    // insect's legs
    glColor3ub(80, 44, 26);
    glBegin(GL_QUADS);
    glVertex2f(x - 18, y - 40); //1
    glVertex2f(x + 18, y - 40); //2
    glVertex2f(x + 6, y - 46); //4
    glVertex2f(x - 6, y - 46); //3
    glEnd();

    glColor3ub(80, 44, 26);
    glBegin(GL_QUADS);
    glVertex2f(x - 15, y - 54); //5
    glVertex2f(x + 15, y - 54); //6
    glVertex2f(x + 6, y - 59); //8
    glVertex2f(x - 6, y - 59); //7
    glEnd();

    glColor3ub(80, 44, 26);
    glBegin(GL_QUADS);
    glVertex2f(x - 20, y - 66); //9
    glVertex2f(x + 20, y - 66); //10
    glVertex2f(x + 22, y - 69); //12
    glVertex2f(x - 22, y - 69); //11
    glEnd();

    glColor3ub(80, 44, 26);
    glBegin(GL_QUADS);
    glVertex2f(x - 20, y - 74); //9*
    glVertex2f(x + 20, y - 74); //10*
    glVertex2f(x + 22, y - 77); //12*
    glVertex2f(x - 22, y - 77); //11*
    glEnd();

    // insects's body
    glColor3ub(121, 66, 39);
    circle(x, y - 43, 10);
    glColor3ub(80, 44, 26);
    circle_wire(x, y - 43, 10);

    glColor3ub(121, 66, 39);
    circle(x, y - 56, 8);
    glColor3ub(80, 44, 26);
    circle_wire(x, y - 56, 8);

    glColor3ub(121, 66, 39);
    circle(x, y - 72, 13);
    glColor3ub(80, 44, 26);
    circle_wire(x, y - 72, 13);

    // insect's antennae
    glColor3ub(80, 44, 26);
    glBegin(GL_QUADS);
    glVertex2f(x - 10, y - 23); //A
    glVertex2f(x - 7, y - 26); //B
    glVertex2f(x - 2, y - 33); //D
    glVertex2f(x, y - 30); //C
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(x + 10, y - 23); //F
    glVertex2f(x + 7, y - 26); //G
    glVertex2f(x + 2, y - 33); //E
    glVertex2f(x, y - 30); //C
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(x, y - 30); //C
    glVertex2f(x - 2, y - 33); //D
    glVertex2f(x, y - 36); //K
    glVertex2f(x + 2, y - 33); //E
    glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == ' ' && !isBulletFired)
    {
        isBulletFired = true;
        bulletVisible = true;
        targetHit = false;
    }
}

void update()
{

    glPushMatrix();
    displayInsect(insectX, insectY);
    glPopMatrix();

    insectY += insectSpeed; // the movement of the insect

    // to calculate the difference between insect coordinates and insect powder coordinates
    double dx = insectX - insectPowderX;
    double dy = insectY - insectPowderY;

    bulletAngle = atan2(dy, dx);

    //int insectPowderX2 = (insectPowderX * cos(bulletAngle)) - (insectPowderY * sin(bulletAngle)); // to try to make the rotation
    //int insectPowderY2 = (insectPowderY * cos(bulletAngle)) + (insectPowderX * sin(bulletAngle)); // but it does not work :((

    if (isBulletFired)
    {
        glPushMatrix();
        displayInsectPowder(insectPowderX, insectPowderY);
        glPopMatrix();

        // to move insect powder towards insect
        insectPowderX += cos(bulletAngle) * insectPowderSpeed;
        insectPowderY += sin(bulletAngle) * insectPowderSpeed;

    }

    if (!targetHit);
    {

        glPushMatrix();
        displayInsectPowder(insectPowderX, insectPowderY);
        glPopMatrix();

        // Check if insect powder hit the insect
        if (dx == 0 || dy == 0)
        {
            targetHit = true;
            isBulletFired = false;
            bulletVisible = false;

            if (targetHit == true)
            {
                srand(time(NULL));
                int random_number = rand() % 1001 - 500;

                int insectXrandom = random_number; // random X values for insect
                insectY = -297;

                displayInsect(insectX, insectY);

            }
        }
    }
}

void display()
{
    // to call the shapes I draw
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawGradientRectangle();
    glFlush();

    displaySpray(handX, handY);
    displayHand(handX, handY);

    update();

    displayScreen();

    glColor3ub(192, 192, 192);
    vprint2(530, 260, 0.1, "Ece Tugba Cebeci");
    glLineWidth(0.25);

    glColor3ub(192, 192, 192);
    vprint2(-652, 320, 0.15, "Every time you press the space key, a drop of poisonous medicine destroys the insect.");
    glLineWidth(0.30);

    glutSwapBuffers();
    glutPostRedisplay();
}

void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//

void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP:
        up = true;
        break;
    case GLUT_KEY_DOWN:
        down = true;
        break;
    case GLUT_KEY_LEFT:
        left = true;
        break;
    case GLUT_KEY_RIGHT:
        right = true;
        break;
    }


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//

void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP:
        up = false;
        break;
    case GLUT_KEY_DOWN:
        down = false;
        break;
    case GLUT_KEY_LEFT:
        left = false;
        break;
    case GLUT_KEY_RIGHT:
        right = false;
        break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1

void onClick(int button, int stat, int x, int y)
{
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


int  main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sad Death of Insects");

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(onResize);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

    Init();
    glutMainLoop();

    return(0);
}
