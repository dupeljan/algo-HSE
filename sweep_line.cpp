#include "sweep_line.h"
using namespace sweep_line;
Sweep_line::Sweep_line()
{

}

seg_pair *Sweep_line::get_first_interception(const seg_vect segment_vect)
{
    using namespace ttt;
    // Make events queue
    std::vector<std::pair<double,Segment_part>> events_queue;
    for(auto segment : segment_vect)
    {
        auto ptr = std::make_shared<Segment>(segment);
        for(auto &status : All_statuses)
        {
            auto x = Segment_part(ptr,status);
            events_queue.push_back(std::make_pair(x.get_key(),x));
        }
    }

    // Sort event queue by x coord
    quick_sort<Segment_part>(events_queue);
    // Create an empty 2-3 tree
    ttt::Two_thee_tree segment_list;
    for(auto &event : events_queue)
    {
        auto cur_segment_ptr = event.second.segment;
        auto key = cur_segment_ptr->a.y;

        switch (event.second.get_status())
        {
        case start:
        {
            // Insert segment into tree
            segment_list.insert(key,cur_segment_ptr);
            // Check interceptions
            auto cur_segment = *cur_segment_ptr.get();
            auto next = Node::get_value_shrd_ptr(segment_list.next(key));
            if (cur_segment * next )
                return new seg_pair(cur_segment,*next.get());
            auto prev = Node::get_value_shrd_ptr(segment_list.prev(key));
            if (cur_segment * prev)
                return new seg_pair(cur_segment,*prev.get());
            break;
        }
        case end:
        {
            auto prev = Node::get_value_shrd_ptr(segment_list.next(key));
            auto next = Node::get_value_shrd_ptr(segment_list.prev(key));
            if(prev != nullptr && *prev.get() * next)
                return new seg_pair(*prev.get(),*next.get());
            segment_list.remove(key);
            break;
         }

        }
    }
    // If there is no one interception
    return nullptr;
}

seg_vect Sweep_line::gen_segments(int count)
{

}
