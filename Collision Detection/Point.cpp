// Point struct implementation

#include "Point.h"

// I'm hoping this setup means you can't get a Point without it having x and y set. We don't want that!
template <typename IntDouble>
Point<IntDouble>::Point(IntDouble x, IntDouble y) {}
