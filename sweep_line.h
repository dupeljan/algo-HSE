#ifndef SWEEP_LINE_H
#define SWEEP_LINE_H

#include <algorithm>
#include <utility>
#include <memory>
#include <vector>
#include "quick_sort.h"
#include "two_three_tree.h"
#include "segment.h"

namespace sweep_line {


class Sweep_line
{
    std::vector<Segment> v;
public:
    Sweep_line();
    std::unique_ptr<std::pair<Segment,Segment>> get_first_interception();
};

}
#endif // SWEEP_LINE_H
