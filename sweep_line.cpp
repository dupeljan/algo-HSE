#include "sweep_line.h"
using namespace sweep_line;
Sweep_line::Sweep_line()
{

}

std::pair<Segment, Segment> Sweep_line::get_first_interception()
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
        auto cur_segment = event.second.segment;
        auto key = cur_segment->a.y;

        switch (event.second.get_status())
        {
        case start:
            // Insert segment into tree
            segment_list.insert(key,cur_segment);
            // Check interceptions
            if ((*cur_segment) * (*segment_list.prev(key)))
                return std::make_pair((*cur_segment), (*segment_list.prev(key)));
            if ((*cur_segment) * (*segment_list.next(key)))
                return std::make_pair((*cur_segment), (*segment_list.prev(key)));
            break;
        case end:
            auto prev = *segment_list.next(key);
            auto next = *segment_list.prev(key);
            if(prev * next)
                return std::make_pair(prev,next);
            segment_list.remove(key);
            break;

        }
    }
    // If there is no one interception
    return nullptr;
}
