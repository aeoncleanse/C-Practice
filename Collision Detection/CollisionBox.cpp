// CollisionBox struct implementation

#include "CollisionBox.h"
#include "Point.h"
#include "ObjectHandler.h" // Yeah yeah, I didn't make it yet!

CollisionBox::CollisionBox(Point<int> mysize, Point* mypos, ObjectHandler* Owner) {
    sizex = mysize.x;
    sizey = mysize.y;
    pos = mypos;
    owner = Owner;
}
