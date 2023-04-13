#include "graphics.h"
#include "Shapes/rect.h"
#include <iostream>
#include <memory>
#include <vector>
#include <chrono>

using namespace std;

enum Screen {
    startScreen, middleScreen, endScreen
};

// Screen
Screen visual;
GLdouble width, height;
int wd;

// Colors
color grey(.5, .5, .5);
color yellow(1, 1, 0);
color red(1, 0, 0);
color black(0, 0, 0);

// Game variables
vector<vector<Rect>> gameBoard;
int boardHeight = 5;
int boardWidth = 5;
int clickTally = 0;
Rect highlight;

// Timer
chrono::steady_clock::time_point startTime, elapsedTime;

// Creates a 5x5 square grid centered using the width and height of the screen
void initBoard() {
    double squareSize = width / 6;
    double marginSize = squareSize / 5;
    squareSize -= marginSize;
    double boardX = (width - (squareSize + marginSize) * 4) / 2;
    double boardY = (height - (squareSize + marginSize) * 4) / 2;
    double squareX = boardX;
    double squareY = boardY;

    // Populate the 2D game board vector
    vector<Rect> row;
    color squareColor;
    for (int y = 0; y < boardHeight; ++y) {
        row.clear();
        squareX = boardX;
        for (int x = 0; x < boardWidth; ++x) {
            squareColor = rand() % 2 == 0 ? yellow : grey;
            row.push_back(Rect(squareColor, squareX, squareY, dimensions(squareSize, squareSize)));
            squareX += squareSize + marginSize;
        }
        squareY += squareSize + marginSize;
        gameBoard.push_back(row);
    }

    // Init highlight rect
    double highlightSize = squareSize + marginSize / 2;
    highlight = Rect(black, 0, 0, dimensions(highlightSize, highlightSize));
}

void init() {
    srand(time(0));
    width = 500;
    height = 500;
    visual = startScreen;
    initBoard();
    startTime = chrono::steady_clock::now();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0, 0, 0, 1.0f);
}

// Draws a red box around hovered square
void drawHighlight() {
    highlight.draw();
}

// Draws each rectangle of the game board
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
        string message = "The object of the game is to ensure all lights are off.";
        string messageTwo = "Turning a light off or on will switch all adjacent squares";
        string messageThree = "to the opposite state Press the space bar to continue";
        string messageFour = "Press the space bar to continue.";
        glColor3f(1, 1, 1);
        glRasterPos2i(20, 50);
        for (const char &letter: message) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        glRasterPos2i(20, 70);
        for (const char &letter: messageTwo) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        glRasterPos2i(20, 90);
        for (const char &letter: messageThree) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        glRasterPos2i(115, 160);
        for (const char &letter: messageFour) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    } else if (visual == middleScreen) {
        // Draws the game in here
        drawHighlight();
    }

    if (visual == middleScreen) {
        // DRAW THE GAME IN HERE
        drawBoard();
        string tallyMessage = "Click Tally: " + to_string(clickTally);
        glColor3f(1, 1, 1);
        glRasterPos2i(0, 30);
        for (const char &letter: tallyMessage) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        int winTally = 0;
        for (int i = 0; i < gameBoard.size(); ++i) {
            for (int j = 0; j < gameBoard.size(); ++j) {
                if(gameBoard[i][j].getColor() == grey){
                    winTally++;
                }
            }
        }
        if (winTally == 25) {
            visual = endScreen;
        }
        glutPostRedisplay();
        // win condition: if loop that switches it to the endScreen
    } else if (visual == endScreen) {

    }

    if (visual == endScreen) {
        string lastMessage = "You Win!";
        glColor3f(1, 1, 1);
        glRasterPos2i(115, 160);
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
    glutPostRedisplay();
}

void cursor(int x, int y) {
    // Highlight is invisible on the black background to start
    highlight.setColor(black);
    // Iterates through game board to see if cursor is hovering over any square
    for (int i = 0; i < gameBoard.size(); ++i) {
        for (int j = 0; j < gameBoard[0].size(); ++j) {
            if (gameBoard[i][j].isOverlapping(x, y)) {
                // If cursor is overlapping a square, make the highlight visible at that square
                highlight.setColor(red);
                highlight.setCenter(gameBoard[i][j].getCenter());
            }
        }
    }
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    // Only detect mouse input on middleScreen
    if (visual != middleScreen) {
        glutPostRedisplay();
        return;
    }

    for (int i = 0; i < gameBoard.size(); ++i) {
        for (int j = 0; j < gameBoard[0].size(); ++j) {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && gameBoard[i][j].isOverlapping(x, y)) {
                gameBoard[i][j].swapColor(grey, yellow);
                if (i - 1 >= 0 && i - 1 <= 4) {
                    gameBoard[i - 1][j].swapColor(grey, yellow);
                }
                if (i + 1 >= 0 && i + 1 <= 4) {
                    gameBoard[i + 1][j].swapColor(grey, yellow);
                }
                if (j - 1 >= 0 && j - 1 <= 4) {
                    gameBoard[i][j - 1].swapColor(grey, yellow);
                }
                if (j + 1 >= 0 && j + 1 <= 4) {
                    gameBoard[i][j + 1].swapColor(grey, yellow);
                }
                ++clickTally;
            }
        }
    }

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

//    endTime = chrono::steady_clock::now();
//    cout << "Elapsed time = " << chrono::duration_cast<chrono::seconds>(endTime - startTime).count() << "seconds."
//         << endl;
    return 0;
}
