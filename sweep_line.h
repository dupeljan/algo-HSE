#ifndef SWEEP_LINE_H
#define SWEEP_LINE_H

#include <algorithm>
#include <utility>
#include <memory>
#include <vector>
#include "quick_sort.h"
#include "two_three_tree.h"

namespace sweep_line {

typedef std::pair<Segment,Segment> seg_pair;
typedef std::vector<Segment> seg_vect;

enum Gen_mode {without_interceptions, one_iterception};
class Sweep_line
{

    //std::vector<Segment> v;
public:
    Sweep_line();
    static seg_pair* get_first_interception(const seg_vect segment_vect);
    static seg_pair* get_first_interception_staidforward(const seg_vect segment_vect);
    static std::pair<seg_vect, std::unique_ptr<Segment> > gen_segments(long count = 20000, Gen_mode mode = without_interceptions );
};

}
#endif // SWEEP_LINE_H
