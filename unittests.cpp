#include "gtest/gtest.h"
#include "two_three_tree.h"
#include <cstdlib>
#include <algorithm>
#include <set>
#include "sweep_line.h"

using namespace ttt;
/*
void canonic_tree_test(ttt::Two_thee_tree tree)
{
    EXPECT_EQ (tree.root->child_max,std::vector<double>({4,9}));
    EXPECT_EQ (tree.root->childs[0]->child_max,std::vector<double>({-1,2,4}));
    EXPECT_EQ (tree.root->childs[1]->child_max,std::vector<double>({6,9}));
    EXPECT_EQ (tree.root->childs[0]->childs[0]->child_max,std::vector<double>({-2,-1}));
    EXPECT_EQ (tree.root->childs[0]->childs[1]->child_max,std::vector<double>({1,2}));
    EXPECT_EQ (tree.root->childs[0]->childs[2]->child_max,std::vector<double>({3,4}));
    EXPECT_EQ (tree.root->childs[0]->childs[0]->childs[0]->key,-2);
    EXPECT_EQ (tree.root->childs[0]->childs[0]->childs[1]->key,-1);
    EXPECT_EQ (tree.root->childs[0]->childs[1]->childs[0]->key,1);
    EXPECT_EQ (tree.root->childs[0]->childs[1]->childs[1]->key,2);
    EXPECT_EQ (tree.root->childs[0]->childs[2]->childs[0]->key,3);
    EXPECT_EQ (tree.root->childs[0]->childs[2]->childs[1]->key,4);
    EXPECT_EQ (tree.root->childs[1]->childs[0]->child_max,std::vector<double>({5,6}));
    EXPECT_EQ (tree.root->childs[1]->childs[1]->child_max,std::vector<double>({7,8,9}));
    EXPECT_EQ (tree.root->childs[1]->childs[0]->childs[0]->key,5);
    EXPECT_EQ (tree.root->childs[1]->childs[0]->childs[1]->key,6);
    EXPECT_EQ (tree.root->childs[1]->childs[1]->childs[0]->key,7);
    EXPECT_EQ (tree.root->childs[1]->childs[1]->childs[1]->key,8);
    EXPECT_EQ (tree.root->childs[1]->childs[1]->childs[2]->key,9);

}

TEST(TTTtreeTest, insert_test)
{

    auto tree = ttt::Two_thee_tree();
    auto canonic_tree_insert = std::vector<key_type>({3,2,1,4,5,6,7,8,9,-1,-2});
    // Insert something to this tree
    for(auto &i : canonic_tree_insert)
        tree.insert(i,nullptr);

    canonic_tree_test(tree);

    // Try random shuffle
    for(int i = 0; i < 100; i++)
    {
        std::random_shuffle(canonic_tree_insert.begin(), canonic_tree_insert.end());
        canonic_tree_test(tree);
    }
}

TEST(TTTtreeTest, remove_test)
{
    auto tree = ttt::Two_thee_tree();

    // Empty case
    tree.remove(5);

    // Only root case
    tree.insert(5,nullptr);
    tree.remove(5);
    tree.remove(5);
    EXPECT_EQ(tree.root,nullptr);

    // Parent has tree elelents case
    auto canonic_tree_insert = std::vector<key_type>({3,2,1,4,5,6,7,8,9,-1,-2});
    for (auto &i : canonic_tree_insert)
        tree.insert(i,nullptr);
    tree.insert(-3,nullptr);
    tree.remove(-3);
    canonic_tree_test(tree);

    auto tree1 = ttt::Two_thee_tree();
    tree1.insert(1,nullptr);
    tree1.insert(1,nullptr);
    tree1.insert(2,nullptr);
    tree1.remove(1);
    EXPECT_EQ(tree1.root->key,2);
    EXPECT_EQ(tree1.root->parent,nullptr);

    tree.insert(-3,nullptr);
    for (auto &i : canonic_tree_insert)
        tree.remove(i);
    EXPECT_EQ(tree.root->key,-3);
    tree.remove(-3);

    // HARD TEST
    for (auto &i : canonic_tree_insert)
        tree.insert(i,nullptr);
    int min(10), max(10000);
    for(int i=0; i<10; i++)
    {
        auto v1 = std::vector<key_type>(10000);
        auto v2 = std::vector<key_type>(10000);
        std::generate(v1.begin(), v1.end(),
                      [min, max]() -> key_type {return std::rand() % (max - min) + min; });
        auto tmp = max;
        max = -min;
        min = -tmp;
        std::generate(v2.begin(), v2.end(),
                      [max, min]() -> key_type {return std::rand() % (max - min) + min; });
        v1.insert( v1.end(), v2.begin(), v2.end() );

        std::random_shuffle(v1.begin(),v1.end());
        for(auto &x : v1)
            tree.insert(x,nullptr);
        std::random_shuffle(v1.begin(),v1.end());
        for(auto &x : v1)
            EXPECT_EQ(tree.search(x)->key,x);
        std::random_shuffle(v1.begin(),v1.end());
        for(auto &x: v1)
            tree.remove(x);
        canonic_tree_test(tree);
    }

}

TEST(TTTtreeTest,next_pred_test)
{

    const int ITER = 10;
    int min(-100000), max(100000);
    auto tree = ttt::Two_thee_tree();
    for(int i=0; i < ITER; i++)
    {

        // Create random vector
        auto v = std::vector<key_type>(10000);
        std::generate(v.begin(), v.end(),
                      [min, max]() -> key_type {return std::rand() % (max - min) + min; });
        // Push it into tree
        for(auto &x : v)
            tree.insert(x,nullptr);

        // Sort and remove unique elemns
        std::sort( v.begin(), v.end() );
        v.erase( std::unique( v.begin(), v.end() ), v.end() );

        // Assign order in tree
        for(auto x = v.begin()+1; (x + 1) != v.end(); ++x)
        {
            EXPECT_EQ(tree.next(*x)->key,*(x+1));
            EXPECT_EQ(tree.prev(*x)->key,*(x-1));
        }
        EXPECT_EQ(tree.next(v.back()),nullptr);
        EXPECT_EQ(tree.prev(v[0]),nullptr);

        tree =  ttt::Two_thee_tree();
    }

}
*/


TEST(QuicksortTest, sort_test)
{


    const int max = 50000;
    const int min = -50000;

    for(int i = 0; i < 100; i++)
    {
        std::vector<std::pair<Segment_part_key,int>> v(10000);
        // Fill it with random numbers
        std::generate(v.begin(), v.end(),
                      [min, max]() -> std::pair<Segment_part_key,int> {return std::make_pair(Segment_part_key(std::rand() % (max - min) + min,
                                                            start),0); });
        // Sort it and assert
        quick_sort<int>(v);
        EXPECT_EQ(is_sorted<int>(v),true) ;
    }
}


TEST(SegmentTest, intersection_test)
{
    using namespace sweep_line;
    // Parallel lines
    Segment a(Point(1,2),Point(3,2));
    Segment b(Point(0,4),Point(10,4));
    EXPECT_EQ(a*b,false);
    // Intercept lines
    Segment c(Point(0,0),Point(4,50));
    EXPECT_EQ(b*c,true);
    // Not intercept but not parallel
    EXPECT_EQ(a*c,false);
}

TEST(SegmentTest, complex_copmarison_test)
{
     using namespace ttt;
     Segment a(Point(1,2),Point(4,5));
     EXPECT_EQ(a.key == a.key,true);
     Segment b(Point(2,4),Point(3,5));
     Segment c(Point(2,-1),Point(4,-2));
     EXPECT_EQ(a.key < b.key, true);
     EXPECT_EQ(c.key < a.key, true);

     // Infinity test
     Segment d(Point(1,3),Point(1,4));
     Segment e(Point(1,4),Point(1,3));
     EXPECT_EQ(d,d);
     EXPECT_EQ(e,e);

}

std::vector<long> get_rand_unique(const int size,long min = -1000000,long max =1000000)
{
    auto v = std::vector<long>(size);
    std::generate(v.begin(), v.end(),
                  [min, max]() -> long {return std::rand() % (max - min) + min; });
    v.erase(std::unique(v.begin(), v.end() ), v.end());
    return v;
}

TEST(Sweep_lineTest,get_frist_interception_simple_cases)
{
    using namespace sweep_line;
    // Gen vector of segments
    {
        seg_vect v;
        v.push_back(Segment(Point(0,0),Point(5,1)));
        v.push_back(Segment(Point(1,-1),Point(5,-3)));
        v.push_back(Segment(Point(2,0),Point(3,4)));
        auto res =  *Sweep_line::get_first_interception(v);
        EXPECT_EQ(res,std::make_pair(Segment(Point(2,0),Point(3,4)),Segment(Point(0,0),Point(5,1))));
    }

    {
        seg_vect v;
        v.push_back(Segment(Point(0,0),Point(5,1)));
        v.push_back(Segment(Point(2,0),Point(3,-4)));
        v.push_back(Segment(Point(1,-1),Point(5,-3)));
        auto res =  *Sweep_line::get_first_interception(v);
        EXPECT_EQ(res,std::make_pair(Segment(Point(2,0),Point(3,-4)),Segment(Point(1,-1),Point(5,-3))));
    }
}
TEST(Sweep_lineTest,get_frist_interception_test_parallel_line)
{
    using namespace sweep_line;

    std::cout << "Size of non intercept lines\nAll lines parallel\n";
    // Build list of parallel segment
    const int count = 30;

    for(int i = 0; i < count; i++)
    {
        seg_vect v;
        auto x = get_rand_unique(1000000);
        auto y = get_rand_unique(1000000);
        auto len = get_rand_unique(1000000);
        double slope = 30 * (std::rand() % 1000 ) / (double) 1000.;

        // Add only parallel lines
        int k = 0;
        for(int i = 0; i < std::min(std::min(x.size(),y.size()),len.size()); i++)
        {
            auto seg = Segment(Point(x[i],y[i]),Point(x[i]+len[i],y[i] + len[i] * slope));
            auto k_old = k;
            for(auto &seg_v : v)
                if(seg_v * seg)
                {
                    k++;
                    break;
                }
            if(k_old == k)
                v.push_back(seg);
        }
        std::cout << v.size() << '\n';
        auto res = Sweep_line::get_first_interception(v);
        if (res != nullptr)
        {
            std::cout << "Test is broken or algo is bad!\n";
            EXPECT_EQ(res->first * res->second,true);
        }
    }



}

TEST(Sweep_lineTest,get_frist_interception_test_random_non_interception)
{
    using namespace sweep_line;
    const int count = 30;

    std::cout << "----Pure random------\n";
    for(int i = 0; i < count; i++)
    {
        seg_vect v;
        auto x1 = get_rand_unique(1000000);
        auto y1 = get_rand_unique(1000000);
        auto x2 = get_rand_unique(1000000);
        auto y2 = get_rand_unique(1000000);
        auto sizes = {x1.size(),x2.size(),y1.size(),y2.size()};


        int k = 0;
        for(int i = 0; i < *std::min(sizes.begin(),sizes.end()); i++)
        {
            auto seg = Segment(Point(x1[i],y1[i]),Point(x2[i],y2[i]));
            auto k_old = k;
            for(auto &seg_v : v)
                if(seg_v * seg)
                {
                    k++;
                    break;
                }
            if(k_old == k)
                v.push_back(seg);
        }
        std::cout << v.size() << '\n';
        auto res = Sweep_line::get_first_interception(v);
        if (res != nullptr)
        {
            std::cout << "Test is broken or algo is bad!\n";
            EXPECT_EQ(res->first * res->second,true);
        }

     }
}
TEST(Sweep_lineTest,get_frist_interception_test_random_one_interception)
{
    using namespace sweep_line;

    const int count = 30;

    // Add one interception to this list
    std::cout << "----Pure random with one interception------\n";
    for(int i = 0; i < count; i++)
    {
        seg_vect v;
        auto x1 = get_rand_unique(1000000);//(5,0,10);
        auto y1 = get_rand_unique(1000000);//(5,0,10);
        auto x2 = get_rand_unique(1000000);//(5,0,10);
        auto y2 = get_rand_unique(1000000);//(5,0,10);
        auto sizes = {x1.size(),x2.size(),y1.size(),y2.size()};

        Segment intercept[2];
        int k = 0;
        for(int i = 0; i < *std::min(sizes.begin(),sizes.end()); i++)
        {
            auto seg = Segment(Point(x1[i],y1[i]),Point(x2[i],y2[i]));
            auto k_old = k;
            for(auto &seg_v : v)
                if(seg_v * seg)
                {
                    if(!k)
                    {
                        intercept[0] = seg;// Remember it
                        intercept[1] = seg_v;
                    }


                    k++;
                    break;
                }
            if(k_old == k || k == 1)
                v.push_back(seg);
        }
        std::cout << v.size() << '\n';
        auto res = Sweep_line::get_first_interception(v);
        // If there is no interceptions
        // Almost impossible
        if(!k)
        {
            EXPECT_EQ(res,nullptr);
            continue;
        }

        // Algo must find that interception
        EXPECT_EQ(std::find(v.begin(),v.end(),intercept[0]) == v.end(),false);
        EXPECT_EQ(std::find(v.begin(),v.end(),intercept[1]) == v.end(),false);
        EXPECT_EQ(intercept[0] * intercept[1], true);

        EXPECT_EQ(res == nullptr,false);
        if(res == nullptr)
            continue;
        EXPECT_EQ(res->first == intercept[0]
               || res->second == intercept[0],true);

     }


}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
