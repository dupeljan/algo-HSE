#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdexcept>
#include <math.h>
#include <functional>

const double EPS(1e-5);

// Ask somebody why it isn't work
// without labmda
const auto cmp_eq =
[](const double a, const double b) -> const bool
{
    return std::abs(b - a) < EPS;
};

const auto get_rand_unique_vector =
[](const long size,const long min = -1000000,const long max =1000000) -> std::vector<long>
{
    auto v = std::vector<long>(size);
    std::generate(v.begin(), v.end(),
                  [min, max]() -> long {return std::rand() % (max - min) + min; });
    v.erase(std::unique(v.begin(), v.end() ), v.end());
    return v;
};

const auto get_rand_long =
[](const long min = -1000000, const long max = 1000000) -> long
{
    return std::rand() % (max - min) + min;
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

   const bool operator == (const Point& rhs)
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
    Point beg,end;
    double slope;

    const bool operator<(const ttt_key& rhs)
    {
        auto l = *this;
        auto r = rhs;
        bool rev = false;
        // rhs begin x have to be >= this key begin x
        if(l.beg.x > r.beg.x)
        {
            std::swap(l,r);
            rev = true;
        }
        bool val = l.beg.y + (r.beg.x - l.beg.x) * l.slope - r.beg.y < EPS;
        return !rev && val || rev && !val;
    }

    const bool operator == (const ttt_key& rhs)
    {
        return (this->beg == rhs.beg && this->end == rhs.end);
    }
    const bool operator <= (const ttt_key& rhs){return (*this) == rhs || (*this) < rhs;}
    //bool operator >= (const ttt_key& rhs){return  rhs <= (*this);}
    //bool operator >  (const ttt_key& rhs){return rhs < (*this);}
};

// True if lines intercept
struct Segment;

const bool operator*(const Segment& lhs,const Segment& rhs);

struct Segment
{
// Start point
Point a;
// End point
Point b;
// Segment slope
double slope;
// Segment key
ttt_key key;

static const int area (Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

static const bool intersect_1 (int a, int b, int c, int d)
{
    if (a > b)  std::swap(a, b);
    if (c > d)  std::swap(c, d);
    return std::max(a,c) <= std::min(b,d);
}


static const bool intersect (const Point a,const Point b,const Point c,const Point d)
{
    return intersect_1 (a.x, b.x, c.x, d.x)
        && intersect_1 (a.y, b.y, c.y, d.y)
        && area(a,b,c) * area(a,b,d) <= 0
        && area(c,d,a) * area(c,d,b) <= 0;
}
ttt_key  get_key() const{ return key; }
Point get_a() const { return a; }
Point  get_b() const{ return b; }

    Segment()
    {}

    Segment(const Segment& s):
    a(s.a),
    b(s.b),
    slope(s.slope),
    key(s.key)
    {}

   Segment(Point start,Point end):
   a(start),
   b(end)
   {
       if(start.x > end.x)
           std::swap(a,b);
       slope = (b.y - a.y) / (double) (b.x - a.x);

       key.beg = a;
       key.end = b;
       key.slope = slope;
   }
/*
   // True if lines intercept
   const bool operator*(const Segment& rhs)
   {
        return intersect(a,b,rhs.a,rhs.b);
   }
*/
   const bool operator *(std::shared_ptr<Segment> rhs)
   {
       return (rhs == nullptr)? false : (*this) * (*rhs.get());
   }
};

inline const bool operator*(const Segment& lhs,const Segment& rhs)
{
     return Segment::intersect(lhs.a,lhs.b,rhs.a,rhs.b);
}


inline const bool operator == (const Segment& lhs,const Segment& rhs)
{
    //auto val = lhs.get_key() == rhs.get_key() && lhs.get_b() == rhs.get_b();
    return lhs.get_key() == rhs.get_key() && lhs.get_b() == rhs.get_b();
}

enum Status {start, end};
static const Status All_statuses[] = {start, end};

// Key which takes into accout
// status of segment part
// start < end if
// start coord is equal
struct Segment_part_key
{
    double key;
    Status status;

    Segment_part_key()
    {
    }

    Segment_part_key(Segment segment, Status status_p)
    {
        status = status_p;
        key = (status == start)? segment.a.x : segment.b.x;
    }

    Segment_part_key(double key_p, Status status_p):
    status(status_p),
    key(key_p)
    {
    }

    const bool operator <( const Segment_part_key& rhs)
    {
        if (cmp_eq(key,rhs.key))
            return status == start &&  rhs.status == end;
        return key - rhs.key < EPS;
     }
};


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
    Segment_part_key get_key(){ return Segment_part_key(*segment.get(),status);}
};



#endif // SEGMENT_H
