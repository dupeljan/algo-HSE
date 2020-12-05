#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdexcept>
#include <math.h>
#include <functional>

const double EPS(1e-5);

const auto cmp_eq =
[](const double a, const double b) -> bool
{
    return std::abs(b - a) < EPS;
};


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

   bool operator == (const Point& rhs)
   {
       return cmp_eq(x,rhs.x) && cmp_eq(y,rhs.y);
   }
};

/*
 * Key of ttt tree struct
 * Content begin x and slope value
 */
struct ttt_key
{
    Point beg;
    double slope;

    bool operator<(const ttt_key& rhs)
    {
        // rhs begin x have to be >= this key begin x
        if(this->beg.x > rhs.beg.x)
            throw std::invalid_argument( "Right point have to have bigger x arg" );
        return this->beg.y + (rhs.beg.x - this->beg.x) * this->slope - rhs.beg.y < EPS;
    }

    bool operator == (const ttt_key& rhs)
    {
        return (this->beg == rhs.beg && cmp_eq(slope,rhs.slope));
    }
    bool operator <= (const ttt_key& rhs){return (*this) == rhs || (*this) < rhs;}
    //bool operator >= (const ttt_key& rhs){return  rhs <= (*this);}
    //bool operator >  (const ttt_key& rhs){return rhs < (*this);}
};

struct Segment
{
// Start point
Point a;
// End point
Point b;
// Segment slope
double slope;

inline int area (Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline bool intersect_1 (int a, int b, int c, int d)
{
    if (a > b)  std::swap(a, b);
    if (c > d)  std::swap(c, d);
    return std::max(a,c) <= std::min(b,d);
}

bool intersect (Point a, Point b, Point c, Point d)
{
    return intersect_1 (a.x, b.x, c.x, d.x)
        && intersect_1 (a.y, b.y, c.y, d.y)
        && area(a,b,c) * area(a,b,d) <= 0
        && area(c,d,a) * area(c,d,b) <= 0;
}

    Segment()
    {}

   Segment(Point start,Point end):
   a(start),
   b(end)
   {
       if(start.x > end.x)
           std::swap(a,b);
       slope = (b.y - a.y) / (double) (b.x - a.x);
   }

   // True if lines intercept
   bool operator*(const Segment& rhs)
   {
        return intersect(a,b,rhs.a,rhs.b);
   }

   bool operator *(std::shared_ptr<Segment> rhs)
   {
       return (rhs == nullptr)? false : (*this) * (*rhs.get());
   }
};

enum Status {start, end};
static const Status All_statuses[] = {start, end};

class Segment_part
{
    Status status;
public:
    std::shared_ptr<Segment> segment;

    Segment_part(std::shared_ptr<Segment> segment_, Status status_):
        status(status_),
        segment(segment_)
    {}

    Status get_status(){return status;}
    double get_key(){ return (status == start)? segment->a.x : segment->b.x;}
};
#endif // SEGMENT_H
