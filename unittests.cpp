#include "gtest/gtest.h"
#include "two_three_tree.h"
#include <cstdlib>
#include <algorithm>
#include <set>
#include "quick_sort.h"
#include "sweep_line.h"

void canonic_tree_test(ttt::Two_thee_tree tree)
{
    EXPECT_EQ (tree.root->child_max,std::vector<int>({4,9}));
    EXPECT_EQ (tree.root->childs[0]->child_max,std::vector<int>({-1,2,4}));
    EXPECT_EQ (tree.root->childs[1]->child_max,std::vector<int>({6,9}));
    EXPECT_EQ (tree.root->childs[0]->childs[0]->child_max,std::vector<int>({-2,-1}));
    EXPECT_EQ (tree.root->childs[0]->childs[1]->child_max,std::vector<int>({1,2}));
    EXPECT_EQ (tree.root->childs[0]->childs[2]->child_max,std::vector<int>({3,4}));
    EXPECT_EQ (tree.root->childs[0]->childs[0]->childs[0]->key,-2);
    EXPECT_EQ (tree.root->childs[0]->childs[0]->childs[1]->key,-1);
    EXPECT_EQ (tree.root->childs[0]->childs[1]->childs[0]->key,1);
    EXPECT_EQ (tree.root->childs[0]->childs[1]->childs[1]->key,2);
    EXPECT_EQ (tree.root->childs[0]->childs[2]->childs[0]->key,3);
    EXPECT_EQ (tree.root->childs[0]->childs[2]->childs[1]->key,4);
    EXPECT_EQ (tree.root->childs[1]->childs[0]->child_max,std::vector<int>({5,6}));
    EXPECT_EQ (tree.root->childs[1]->childs[1]->child_max,std::vector<int>({7,8,9}));
    EXPECT_EQ (tree.root->childs[1]->childs[0]->childs[0]->key,5);
    EXPECT_EQ (tree.root->childs[1]->childs[0]->childs[1]->key,6);
    EXPECT_EQ (tree.root->childs[1]->childs[1]->childs[0]->key,7);
    EXPECT_EQ (tree.root->childs[1]->childs[1]->childs[1]->key,8);
    EXPECT_EQ (tree.root->childs[1]->childs[1]->childs[2]->key,9);

}

TEST(TTTtreeTest, insert_test)
{

    auto tree = ttt::Two_thee_tree();
    auto canonic_tree_insert = std::vector<int>({3,2,1,4,5,6,7,8,9,-1,-2});
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
    auto canonic_tree_insert = std::vector<int>({3,2,1,4,5,6,7,8,9,-1,-2});
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
        auto v1 = std::vector<int>(10000);
        auto v2 = std::vector<int>(10000);
        std::generate(v1.begin(), v1.end(),
                      [min, max]() -> int {return std::rand() % (max - min) + min; });
        auto tmp = max;
        max = -min;
        min = -tmp;
        std::generate(v2.begin(), v2.end(),
                      [max, min]() -> int {return std::rand() % (max - min) + min; });
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
        auto v = std::vector<int>(10000);
        std::generate(v.begin(), v.end(),
                      [min, max]() -> int {return std::rand() % (max - min) + min; });
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

TEST(QuicksortTest, sort_test)
{


    const int max = 50000;
    const int min = -50000;

    for(int i = 0; i < 100; i++)
    {
        std::vector<std::pair<double,int>> v(10000);
        // Fill it with random numbers
        std::generate(v.begin(), v.end(),
                      [min, max]() -> std::pair<double,int> {return std::make_pair(std::rand() % (max - min) + min,0); });
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
