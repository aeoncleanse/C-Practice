// Point.h contains a struct for X and Y coordinate data

#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

// I want to limit this to ints and doubles. How?
template <typename IntDouble>
struct Point {
    Point(IntDouble x, IntDouble y);

    IntDouble x;
    IntDouble y;
};

#endif // POINT_H_INCLUDED
