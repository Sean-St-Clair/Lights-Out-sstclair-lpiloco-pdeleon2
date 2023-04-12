#include "../graphics.h"
#include "rect.h"
#include <iostream>

using namespace std;

/********************* Dimensions Struct ********************/

dimensions::dimensions() : width(0), height(0) {}

dimensions::dimensions(double w, double h) : width(w), height(h) {}

ostream &operator<<(ostream &outs, const dimensions &d) {
    outs << "[" << d.width << ", " << d.height << "]";
    return outs;
}


Rect::Rect() : Shape(), size({0, 0}) {
}

Rect::Rect(dimensions size) : Shape() {
    setSize(size);
}

Rect::Rect(color fill) : Shape(fill), size({0, 0}) {
}

Rect::Rect(point2D center) : Shape(center), size({0, 0}) {
}

Rect::Rect(color fill, point2D center) : Shape(fill, center), size({0, 0}) {
}

Rect::Rect(double red, double green, double blue, double alpha) : Shape(red, green, blue, alpha), size({0, 0}) {
}

Rect::Rect(double x, double y) : Shape(x, y), size({0, 0}) {
}

Rect::Rect(double red, double green, double blue, double alpha, double x, double y) : Shape(red, green, blue, alpha, x,
                                                                                            y), size({0, 0}) {
}

Rect::Rect(color fill, double x, double y) : Shape(fill, x, y), size({0, 0}) {
}

Rect::Rect(double red, double green, double blue, double alpha, point2D center) : Shape(red, green, blue, alpha,
                                                                                        center), size({0, 0}) {
}

Rect::Rect(color fill, dimensions size) : Shape(fill) {
    setSize(size);
}

Rect::Rect(point2D center, dimensions size) : Shape(center) {
    setSize(size);
}

Rect::Rect(color fill, point2D center, dimensions size) : Shape(fill, center) {
    setSize(size);
}

Rect::Rect(double red, double green, double blue, double alpha, dimensions size) : Shape(red, green, blue, alpha) {
    setSize(size);
}

Rect::Rect(double x, double y, dimensions size) : Shape(x, y) {
    setSize(size);
}

Rect::Rect(double red, double green, double blue, double alpha, double x, double y, dimensions size) : Shape(red, green,
                                                                                                             blue,
                                                                                                             alpha, x,
                                                                                                             y) {
    setSize(size);
}

Rect::Rect(color fill, double x, double y, dimensions size) : Shape(fill, x, y) {
    setSize(size);
}

Rect::Rect(double red, double green, double blue, double alpha, point2D center, dimensions size) : Shape(red, green,
                                                                                                         blue, alpha,
                                                                                                         center) {
    setSize(size);
}

dimensions Rect::getSize() const {
    return size;
}

double Rect::getWidth() const {
    return size.width;
}

double Rect::getHeight() const {
    return size.height;
}

double Rect::getLeftX() const {
    return center.x - (size.width / 2.0);
}

double Rect::getRightX() const {
    return center.x + (size.width / 2.0);
}

double Rect::getTopY() const {
    return center.y - (size.height / 2.0);
}

double Rect::getBottomY() const {
    return center.y + (size.height / 2.0);
}

void Rect::setSize(dimensions size) {
    if (size.width >= 0 && size.height >= 0) {
        this->size = size;
    }
}

void Rect::setSize(double width, double height) {
    setSize({width, height});
}

void Rect::setWidth(double width) {
    setSize({width, size.height});
}

void Rect::setHeight(double height) {
    setSize({size.width, height});
}

void Rect::changeSize(double deltaWidth, double deltaHeight) {
    setSize({size.width + deltaWidth, size.height + deltaHeight});
}

void Rect::changeWidth(double delta) {
    setSize({size.width + delta, size.height});
}

void Rect::changeHeight(double delta) {
    setSize({size.width, size.height + delta});
}

bool Rect::isOverlapping(const Rect &r) const {
    // If rectangles are overlapping, the distances between their center points will be
    // less than their combined widths / heights along the x and y axes, respectively.
    double sumHalfWidths = size.width / 2 + r.size.width / 2;
    double sumHalfHeights = size.height / 2 + r.size.height / 2;
    bool xOverlap = false;
    bool yOverlap = false;
    // 1. Along the x-axis
    if (abs(center.x - r.center.x) <= sumHalfWidths) {
        xOverlap = true;
    }
    // 2. Along the y-axis
    if (abs(center.y - r.center.y) <= sumHalfHeights) {
        yOverlap = true;
    }
    return (xOverlap && yOverlap);
}

void Rect::draw() const {
    // Don't forget to set the color to the fill field
    glColor4f(fill.red, fill.green, fill.blue, fill.alpha);
    glBegin(GL_QUADS);
    // glVertex2i takes a 2-D (x, y) coordinate
    glVertex2i(center.x - size.width / 2, center.y - size.height / 2);
    glVertex2i(center.x - size.width / 2, center.y + size.height / 2);
    glVertex2i(center.x + size.width / 2, center.y + size.height / 2);
    glVertex2i(center.x + size.width / 2, center.y - size.height / 2);
    glEnd();
}