#include "graphics.h"
#include "Shapes/rect.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

enum Screen {
    startScreen, middleScreen, endScreen
};

Screen visual;
GLdouble width, height;
int wd;

// Colors
color grey(.5, .5, .5);
color yellow(1, 1, 0);

// Game variables
Rect user;

// Board
vector<vector<Rect>> gameBoard;

void initUser() {
    // Initialize the user to be a 20x20 white block
    // centered in the top left corner of the graphics window
    dimensions userDim = dimensions(20, 20);
    user = Rect(color(1, 1, 1), 20, 20, userDim);
}

// Creates a 5x5 square grid centered using the width and height of the screen
void initBoard() {
    int squareSize = width / 6;
    int marginSize = squareSize / 4;
    squareSize -= marginSize;
    int boardX = (width - (squareSize + marginSize) * 4) / 2;
    int boardY = (height - (squareSize + marginSize) * 4) / 2;
    int squareX = boardX;
    int squareY = boardY;

    // Populate the 2D game board vector
    vector<Rect> row;
    for (int y = 0; y < 5; ++y) {
        row.clear();
        squareX = boardX;
        for (int x = 0; x < 5; ++x) {
            row.push_back(Rect(yellow, squareX, squareY, dimensions(squareSize, squareSize)));
            squareX += squareSize + marginSize;
        }
        squareY += squareSize + marginSize;
        gameBoard.push_back(row);
    }
}

void init() {
    width = 500;
    height = 500;
    srand(time(0));
    visual = startScreen;
    initUser();
    initBoard();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0, 0, 0, 1.0f);
}

// TODO: good comments
void drawBoard() {
    for (vector<Rect> &row: gameBoard) {
        for (Rect &r: row) {
            r.draw();
        }
    }
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

    if (visual == startScreen) {
        //Save the start screen message, then print it
        string message = "The object of the game is to ensure all lights are off. Turning a light off or"
                         "on will switch all adjacent squares to the opposite state. Press the spacebar to"
                         "continue";
        glColor3f(1, 1, 1);
        glRasterPos2i(0, 50);
        for (const char &letter: message) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    if (visual == middleScreen) {
        // DRAW THE GAME IN HERE

        drawBoard();

        user.draw();

        // win condition: if loop that switches it to the endScreen
    }

    if (visual == endScreen) {
        string lastMessage = "You Win!";
        glColor3f(1, 1, 1);
        glRasterPos2i(0, 30);
        for (const char &letter: lastMessage) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    // Allows the start screen to transition to the middle screen with user input
    if (visual == startScreen && key == ' ') {
        visual = middleScreen;
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
    for (int i = 0; i < gameBoard.size(); ++i) {
        for (int j = 0; j < gameBoard.size(); ++j){
            if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && gameBoard[i][j].isOverlapping(x, y) && gameBoard[i][j].getColor() == yellow) {
                gameBoard[i][j].setColor(grey);
                gameBoard[i - 1][j].setColor(grey);
                gameBoard[i][j - 1].setColor(grey);
                gameBoard[i + 1][j].setColor(grey);
                gameBoard[i][j + 1].setColor(grey);

            }else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && gameBoard[i][j].isOverlapping(x, y) && gameBoard[i][j].getColor() == grey){
                gameBoard[i][j].setColor(yellow);
                gameBoard[i - 1][j].setColor(yellow);
                gameBoard[i][j - 1].setColor(yellow);
                gameBoard[i + 1][j].setColor(yellow);
                gameBoard[i][j + 1].setColor(yellow);
            }
        }
    }
    glutPostRedisplay();
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

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
