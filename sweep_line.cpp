#include "sweep_line.h"
using namespace sweep_line;
Sweep_line::Sweep_line()
{

}

std::unique_ptr<std::pair<Segment, Segment> > Sweep_line::get_first_interception()
{
    // Make events queue
    std::vector<std::pair<double,Segment_part>> events_queue;
    for(auto &segment : v)
    {
        auto ptr = std::shared_ptr<Segment>(&segment);
        for(auto &status : All_statuses)
        {
            auto x = Segment_part(ptr,status);
            events_queue.push_back(std::make_pair(x.get_status(),x));
        }
    }

    // Sort event queue by x coord
    quick_sort<Segment_part>(events_queue);
    // Create an empty 2-3 tree
    ttt::Two_thee_tree segment_list;
    for(auto &event : events_queue)
    {
        switch (event.second.get_status())
        {
        case start:
            // Insert segment into tree
            segment_list.insert(event.second.segment->a.y,event.second.segment);
            break;
        case end:

            break;

        }
    }
}
