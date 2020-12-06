#include "sweep_line.h"
using namespace sweep_line;
Sweep_line::Sweep_line()
{

}

seg_pair *Sweep_line::get_first_interception(const seg_vect segment_vect)
{
    using namespace ttt;
    // Make events queue
    std::vector<std::pair<Segment_part_key,Segment_part>> events_queue;
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
        auto key = cur_segment_ptr->key;

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

/*
 * Straidforward algotithm for
 * first interception search
 */
seg_pair *Sweep_line::get_first_interception_staidforward(const seg_vect segment_vect)
{
    for(int i = 0; i < segment_vect.size(); i++)
        for(int j = 0; j < i; j++)
            if(segment_vect[i] * segment_vect[j])
                return new seg_pair(segment_vect[i],segment_vect[j]);
    return nullptr;
}

/*
 * Gen segment list with
 * at least one interception if such mode givem
 * params:
 *          count - size of segments which algo trying to add
 * return:
 *          pair:
 *             first - result segment vector
 *             second - segment, which intercept others and have to be
 *                      in the output of get_first_interception
 *                      if mode == one_iterception
 *                      else nullptr
 */
std::pair<seg_vect, std::unique_ptr<Segment>> Sweep_line::gen_segments(long count, Gen_mode mode)
{
     seg_vect v;

     auto gen_rand_segment =
     [](long len = 3) -> Segment
     {
        long x1(get_rand_long()),y1(get_rand_long());
        long slope = get_rand_long() % 300;
             return Segment(Point(x1,y1),Point(x1+len,y1+len * slope));
     };

     auto is_intercept =
             [](Segment seg,seg_vect v) -> bool
     {
           bool res = true;
           for(auto &x : v)
               if(x * seg)
               {
                   res = false;
                   break;
               }
           return res;
     };

     auto k = 0;
     while (k < count)
     {
          auto seg = gen_rand_segment();
          if(is_intercept(seg,v))
          {
            k++;
            v.push_back(seg);
          }
      }

     if(mode == one_iterception)
     {
        Segment seg;
        do
        {
         seg = gen_rand_segment();
        }while(!is_intercept(seg,v));
        v.push_back(seg);
        return std::make_pair(v,std::make_unique<Segment>(Segment(seg)));
     }
     return std::make_pair(v,nullptr);
}

