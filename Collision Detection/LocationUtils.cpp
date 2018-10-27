// Utility functions used by Point and Point derivatives

#include "Point.h"

int mapx;
int mapy;

void HandleIllegal(Point* point) {
    std::clamp(point.posx, 0, mapx);
    std::clamp(point.posy, 0, mapy);
}

void UpdatePosition(Point* loc, Point* newloc) {
    HandleIllegal(newloc);

    *loc = *newloc;
}
