#include "graphics.h"
#include "Shapes/circle.h"
#include "Shapes/rect.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

GLdouble width, height;
int wd;
const color white(1, 1, 1);

Rect grass;
vector<Rect> buildings1;
vector<Rect> buildings2;
vector<Rect> buildings3;
Rect user;

void initUser() {
    // Initialize the user to be a 20x20 white block
    // centered in the top left corner of the graphics window
    dimensions userDim = dimensions(20, 20);
    user = Rect(white, 20, 20, userDim);
}

void init() {
    width = 500;
    height = 500;
    srand(time(0));
    initUser();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0, 0, 0, 1.0f);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    /*
     * Draw here
     */

    user.draw();

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_DOWN:

            break;
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_UP:

            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {
    // Sets the user's center point to be the coordinates
    // passed in as parameters to this function. This will make
    // the user block move with the mouse.
    user.setCenter(x, y);
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    glutPostRedisplay();
}

void buildingTimer(int dummy) {
    // Smallest buildings move fastest
    for (int i = 0; i < buildings1.size(); ++i) {
        // Move all the red buildings to the left
        buildings1[i].moveX(-3);
        // If a shape has moved off the screen
        if (buildings1[i].getCenterX() < -(buildings1[i].getWidth() / 2)) {
            // Set it to the right of the screen so that it passes through again
            int buildingOnLeft = (i == 0) ? buildings1.size() - 1 : i - 1;
            buildings1[i].setCenterX(
                    buildings1[buildingOnLeft].getCenterX() + buildings1[buildingOnLeft].getWidth() / 2 +
                    buildings1[i].getWidth() / 2 + 5);
        }
    }

    // Medium buildings move slower
    for (int i = 0; i < buildings2.size(); ++i) {
        // Move all the red buildings to the left
        buildings2[i].moveX(-2);
        // If a shape has moved off the screen
        if (buildings2[i].getCenterX() < -(buildings2[i].getWidth() / 2)) {
            // Set it to the right of the screen so that it passes through again
            int buildingOnLeft = (i == 0) ? buildings2.size() - 1 : i - 1;
            buildings2[i].setCenterX(
                    buildings2[buildingOnLeft].getCenterX() + buildings2[buildingOnLeft].getWidth() / 2 +
                    buildings2[i].getWidth() / 2 + 5);
        }
    }

    // Largest buildings move slowest
    for (int i = 0; i < buildings3.size(); ++i) {
        // Move all the red buildings to the left
        buildings3[i].moveX(-1);
        // If a shape has moved off the screen
        if (buildings3[i].getCenterX() < -(buildings3[i].getWidth() / 2)) {
            // Set it to the right of the screen so that it passes through again
            int buildingOnLeft = (i == 0) ? buildings3.size() - 1 : i - 1;
            buildings3[i].setCenterX(
                    buildings3[buildingOnLeft].getCenterX() + buildings3[buildingOnLeft].getWidth() / 2 +
                    buildings3[i].getWidth() / 2 + 5);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, buildingTimer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int) width, (int) height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Runner" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, buildingTimer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
