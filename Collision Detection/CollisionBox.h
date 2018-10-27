#ifndef COLLISIONBOX_H_INCLUDED
#define COLLISIONBOX_H_INCLUDED

#include "Point.h"
#include "ObjectHandler.h" // Yeah yeah, I didn't make it yet!

struct CollisionBox {
    CollisionBox(Point<int> mysize, Point* mypos, ObjectHandler* Owner);

    int sizex;
    int sizey;
    Point* pos;
    ObjectHandler* owner;
};

#endif // COLLISIONBOX_H_INCLUDED
