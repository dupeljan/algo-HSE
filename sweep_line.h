#ifndef SWEEP_LINE_H
#define SWEEP_LINE_H

#include <algorithm>
#include <utility>

class Sweep_line
{
    /*
     * Segment class
     */
   struct Point
   {
       double x,y;

       Point():
       x(0),
       y(0)
       {}

       Point(double x_p, double y_p):
       x(x_p),
       y(y_p)
       {}
   };

   class Segment
   {
    // Start point
    Point start;
    // End point
    Point end;
    // Segment slope
    Point a;
    public:
       Segment(T start, T end)
       {
           if(start.x > end.x)
               std::swap(start,end);
           double a = (b.y - a.y) / (double) (b.x - a.x);
       }

       // True if lines intercept
       bool operator*(const Segment& rhs)
       {

       }
   };
public:
    Sweep_line();
};

#endif // SWEEP_LINE_H
