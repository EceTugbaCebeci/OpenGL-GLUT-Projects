/*********
CTIS164
----------
STUDENT : Ece Tuðba Cebeci
SECTION : 004
HOMEWORK: 1 (The Rocket on the sky)
----------
PROBLEMS: My aim is that when the moon is clicked, the color of the sky change but I could not accomplish it.
----------
ADDITIONAL FEATURES: When the clicked anywhere, the window is closed by the pink curtain.
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1400
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  1000 // Period for the timer.
#define TIMER_ON         0 // 0:disable timer, 1:enable timer


/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
bool isCurtain = false;
int  winWidth, winHeight; // current Window width and height

int rocketX = -400, rocketY = 150;
bool isContinue = true;


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


// my window drawings

void displayWindow() // my main window
{
    glColor3ub(25, 49, 97); // the color of the window ground (sky)
    glRectf(-400, 280, 400, -170);

    // the design of the wall
    glColor3ub(204, 90, 17);
    glBegin(GL_LINES);
    glVertex2f(-650, 330);
    glVertex2f(650, 330);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(650, 350);
    glVertex2f(650, -350);
    glEnd();

    // I ignore under the cupboard 

    glBegin(GL_LINES);
    glVertex2f(-650, -350);
    glVertex2f(-650, 350);
    glEnd();


}

void displayLeftOfWindowFrame() // I want to split the window to left and right to make my drawing easier
{
    glColor3ub(139, 121, 94); // the color of the frame
    glRectf(-400, -170, -380, 280);

    glColor3ub(139, 121, 94);
    glRectf(-15, -170, 15, 280);

    glColor3ub(139, 121, 94);
    glRectf(-400, 260, 10, 280);

    glColor3ub(139, 121, 94);
    glRectf(-400, -170, 10, -150);

    glColor3ub(139, 121, 94);
    glRectf(-400, -80, -10, -60);

}

void displayRightOfWindowFrame()
{
    glColor3ub(139, 121, 94);
    glRectf(10, 280, 400, 260);

    glColor3ub(139, 121, 94);
    glRectf(10, -150, 400, -170);

    glColor3ub(139, 121, 94);
    glRectf(380, -170, 400, 280);

    glColor3ub(139, 121, 94);
    glRectf(10, -60, 400, -80);

}

void displayStand() // bench in front of the window
{
    glColor3ub(95, 119, 52); // the color of the stand (or bench)

    glBegin(GL_QUADS);
    glVertex2f(-400, -170);
    glVertex2f(400, -170);
    glVertex2f(500, -230);
    glVertex2f(-500, -230);
    glEnd();

    glColor3ub(75, 94, 43);
    glRectf(-500, -250, 500, -230);

    glColor3ub(119, 151, 65);
    glRectf(-500, -400, 500, -250);

}

void displayFrame() // lines around shapes
{
    // lines for window

    glColor3ub(74, 68, 40);

    glBegin(GL_LINES);
    glVertex2f(-400, 280);
    glVertex2f(-400, -170);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-400, -170);
    glVertex2f(400, -170);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(400, -170);
    glVertex2f(400, 280);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(400, 280);
    glVertex2f(-400, 280);
    glEnd();


    glBegin(GL_LINES);
    glVertex2f(-380, 260);
    glVertex2f(-380, -60);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-380, -60);
    glVertex2f(-15, -60);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-15, 260);
    glVertex2f(-15, -60);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-15, 260);
    glVertex2f(-380, 260);
    glEnd();


    glBegin(GL_LINES);
    glVertex2f(-380, -80);
    glVertex2f(-380, -150);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-15, -150);
    glVertex2f(-380, -150);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-15, -80);
    glVertex2f(-15, -150);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-15, -80);
    glVertex2f(-380, -80);
    glEnd();


    glBegin(GL_LINES);
    glVertex2f(15, 260);
    glVertex2f(380, 260);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(380, 260);
    glVertex2f(380, -60);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(380, -60);
    glVertex2f(15, -60);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(15, -60);
    glVertex2f(15, 260);
    glEnd();


    glBegin(GL_LINES);
    glVertex2f(15, -80);
    glVertex2f(380, -80);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(380, -80);
    glVertex2f(380, -150);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(380, -150);
    glVertex2f(15, -150);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(15, -150);
    glVertex2f(15, -80);
    glEnd();

    // lines for bench in front of the window

    glBegin(GL_LINES);
    glVertex2f(-400, -170);
    glVertex2f(400, -170);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(400, -170);
    glVertex2f(500, -230);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(500, -230);
    glVertex2f(-500, -230);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-500, -230);
    glVertex2f(-400, -170);
    glEnd();

    // lines for the little rectangle between bench and cupboard

    glBegin(GL_LINES);
    glVertex2f(-500, -230);
    glVertex2f(-500, -250);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-500, -250);
    glVertex2f(500, -250);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(500, -250);
    glVertex2f(500, -230);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(500, -230);
    glVertex2f(-500, -230);
    glEnd();

    // lines for the cupboard

    glBegin(GL_LINES);
    glVertex2f(-500, -250);
    glVertex2f(-500, -400);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(500, -250);
    glVertex2f(500, -400);
    glEnd();


}

void displayMoonAndStar()
{
    glColor3ub(255, 222, 102); // the color of moon
    circle(265, 150, 75); // moon

    glColor3ub(236, 171, 83); // the color of moon circle
    circle_wire(265, 150, 75); // the moon circle

    // the rest of the codes belong to stars code

    glColor3ub(236, 171, 83); // the color of the stars
    circle(-200, 140, 5);

    glColor3ub(236, 171, 83);
    circle(-50, 115, 5);

    glColor3ub(236, 171, 83);
    circle(-380, 0, 6);

    glColor3ub(236, 171, 83);
    circle(52, 50, 5);

    glColor3ub(236, 171, 83);
    circle(360, 50, 6);

    glColor3ub(236, 171, 83);
    circle(45, 250, 4);

    glColor3ub(236, 171, 83);
    circle(-375, 235, 4);

    glColor3ub(236, 171, 83);
    circle(-50, -30, 6);

    glColor3ub(236, 171, 83);
    circle(10, 85, 4);
}

void displayTheRocket(int x, int y)
{
    glColor3ub(207, 207, 207); // the color of the tip of rocket
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x - 70, y + 25);
    glVertex2f(x - 70, y - 25);
    glEnd();

    glColor3ub(140, 0, 0); // the color of the body of rocket
    glRectf(x - 70, y + 25, x - 170, y - 25);

    glColor3ub(207, 207, 207); // the color of the protrusion on the back of the rocket
    glBegin(GL_QUADS);
    glVertex2f(x - 170, y + 20);
    glVertex2f(x - 170, y - 20);
    glVertex2f(x - 175, y - 15);
    glVertex2f(x - 175, y + 15);
    glEnd();

    // details of the rocket
    glBegin(GL_LINES);
    glVertex2f(x - 80, y + 25);
    glVertex2f(x - 80, y - 25);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x - 80, y);
    glVertex2f(x - 70, y);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x - 70, y + 25);
    glVertex2f(x - 70, y - 25);
    glEnd();

    // the window of the rocket
    glColor3ub(100, 149, 237);
    circle(x - 120, y, 23);
    glColor3ub(79, 79, 79);
    circle_wire(x - 120, y, 23);

    // the fire of the rocket
    glColor3ub(255, 165, 0); // the color of the fire layers1
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 195, y);
    glVertex2f(x - 175, y + 20);
    glVertex2f(x - 175, y - 20);
    glEnd();

    glColor3ub(255, 127, 36); // the color of the fire layers2
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 185, y);
    glVertex2f(x - 175, y + 15);
    glVertex2f(x - 175, y - 15);
    glEnd();

    // the details in the tip of the rocket
    glColor3ub(140, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 30, y + 15);
    glVertex2f(x - 30, y - 15);
    glVertex2f(x, y);
    glEnd();

    // the wings of the rocket
    glColor3ub(79, 79, 79);
    glRectf(x - 160, y - 25, x - 150, y - 35);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 160, y - 35);
    glVertex2f(x - 150, y - 35);
    glVertex2f(x - 175, y - 45);
    glEnd();

    glColor3ub(79, 79, 79);
    glRectf(x - 160, y + 35, x - 150, y - 25);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 160, y + 35);
    glVertex2f(x - 150, y + 35);
    glVertex2f(x - 175, y + 45);
    glEnd();


}

void nameTable(int x, int y, int width, int height, char text[]) // it is table that contains my name
{
    glColor3ub(0, 0, 0);
    circle(x, y, 4);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x - width / 2, y - 125);

    glVertex2f(x, y);
    glVertex2f(x + width / 2, y - 125);
    glEnd();

    glColor3ub(213, 166, 166);
    glBegin(GL_QUADS);
    glVertex2f(x - width / 2, y - 125);
    glVertex2f(x + width / 2, y - 125);
    glVertex2f(x + width / 2, y - 125 - height / 2);
    glVertex2f(x - width / 2, y - 125 - height / 2);
    glEnd();

    glColor3ub(128, 0, 0);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - width / 2, y - 125);
    glVertex2f(x + width / 2, y - 125);
    glVertex2f(x + width / 2, y - 125 - height / 2);
    glVertex2f(x - width / 2, y - 125 - height / 2);
    glEnd();

    glLineWidth(2);
    vprint2(x - width / 2 + 15, y - (height + 200) / 2 - 8, 0.16, "%s", text);
}

void patch() // the rocket goes out of the window at the end of the movement period and at the beginning so i patched it
{
    glColor3ub(238, 220, 130);
    glRectf(401, 250, 700, -100);
    glRectf(-401, 250, -700, -100);
}

void curtain()
{
    glColor3ub(255, 99, 71); // the color of the curtain
    glRectf(-400, 280, 400, -170); // the curtain

    // the design-pattern of the curtain
    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, 250);
    glVertex2f(400, 250);
    glEnd();

    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, 220);
    glVertex2f(400, 220);
    glEnd();

    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, 190);
    glVertex2f(400, 190);
    glEnd();

    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, 160);
    glVertex2f(400, 160);
    glEnd();

    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, 130);
    glVertex2f(400, 130);
    glEnd();

    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, 100);
    glVertex2f(400, 100);
    glEnd();

    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, 70);
    glVertex2f(400, 70);
    glEnd();

    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, 40);
    glVertex2f(400, 40);
    glEnd();

    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, 10);
    glVertex2f(400, 10);
    glEnd();

    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, -20);
    glVertex2f(400, -20);
    glEnd();

    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, -50);
    glVertex2f(400, -50);
    glEnd();

    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, -80);
    glVertex2f(400, -80);
    glEnd();

    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, -100);
    glVertex2f(400, -100);
    glEnd();

    glColor3ub(205, 79, 57);
    glBegin(GL_LINES);
    glVertex2f(-400, -130);
    glVertex2f(400, -130);
    glEnd();
}

void display()
{
    glClearColor(238 / 255., 220 / 255., 130 / 255., 0);
    glClear(GL_COLOR_BUFFER_BIT);

    displayWindow();
    displayMoonAndStar();
    displayTheRocket(rocketX, rocketY);

    displayStand();
    displayFrame();
    char text[50] = " Ece Tugba Cebeci";
    nameTable(0, -170, 250, 80, text);
    patch();

    if (isCurtain == true)
        curtain();

    displayLeftOfWindowFrame();
    displayRightOfWindowFrame();

    glutSwapBuffers();
}

void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed
    if (key == 27)
        exit(0);

    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed
    if (key == 27)
        exit(0);

    glutPostRedisplay();
}

void onClick(int button, int stat, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN)

        isCurtain = !isCurtain;

    glutPostRedisplay();
}

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

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void rocketTimer(int v) // to movement of the rocket
{
    if (isContinue) {
        rocketX++;
        glutPostRedisplay();
        glutTimerFunc(17, rocketTimer, 0);
        if (rocketX > 600) {
            rocketX = -400;
        }
    }
}

void keyboardHandler(unsigned char key, int x, int y) // in this case, when press is clicked the movement of the rocket stop
{
    if (key == ' ') {
        isContinue = !isContinue;
        glutTimerFunc(17, rocketTimer, 0);
    }
}

void main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(" Rocket on the Sky ");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    // keyboard registration

    glutKeyboardFunc(onKeyDown);
    glutKeyboardUpFunc(onKeyUp);

    // mouse registration

    glutMouseFunc(onClick);


#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();
    glutKeyboardFunc(keyboardHandler);

    glutTimerFunc(17, rocketTimer, 0);

    glutMainLoop();
}