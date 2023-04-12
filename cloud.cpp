//
// Created by Lisa Dion on 1/9/23.
//

#include "Shapes/circle.h"
#include "cloud.h"
#include "Shapes/rect.h"
using namespace std;

Cloud::Cloud() {
    // Call non-default constructor
    Cloud({1, 1, 1}, 0, 0, 50);
}

Cloud::Cloud(color fill, int x, int y, int width) {
    // width = 80
    // center x = 315
    dimensions bottom(width/2, width/2);
    shapes.push_back(make_unique<Circle>(fill, x-(width/4), y, width/4));
    shapes.push_back(make_unique<Circle>(fill, x+(width/4), y, width/4));
    shapes.push_back(make_unique<Circle>(fill, x+(width/16), y-(width/8), width/4));
    shapes.push_back(make_unique<Rect>(fill, x, y, bottom));
}

void Cloud::moveLeftAndJumpX(int deltaX, int width) {
    for (const unique_ptr<Shape> &s : shapes) {
        // Move all the shapes by deltaX
        s->moveX(deltaX);
        // If a shape has moved off the screen
        if (s->getRightX() < 0) {
            // Set it to the right of the screen so that it passes through again
            s->setCenterX(width + (s->getRightX() - s->getLeftX()) / 2);
        }
    }

}

bool Cloud::isOverlapping(Rect& r) {
    // This method only checks the Rect object in the Cloud
    if (dynamic_cast<Rect&>(*shapes[3]).isOverlapping(r)) {
        return true;
    }
    return false;
}

void Cloud::draw() const {
    for (const unique_ptr<Shape> &s : shapes) {
        s->draw();
    }
}