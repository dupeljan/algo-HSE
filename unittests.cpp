#include "gtest/gtest.h"
#include "two_three_tree.h"
#include <cstdlib>
#include <algorithm>
#include "quick_sort.h"

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
        tree.insert(i);

    canonic_tree_test(tree);

    // Try random shuffle
    for(int i = 0; i < 100; i++)
    {
        std::random_shuffle(canonic_tree_insert.begin(), canonic_tree_insert.end());
        canonic_tree_test(tree);
    }
}

TEST(QuicksortTest, sort_test)
{


    const int max = 50000;
    const int min = -50000;

    std::vector<int> x = {1,1};
    std::swap(x[0],x[1]);

    for(int i = 0; i < 100; i++)
    {
        std::vector<int> v(10000);
        // Fill it with random numbers
        std::generate(v.begin(), v.end(),
                      [min, max]() -> int {return std::rand() % (max - min) + min; });
        // Sort it and assert
        quick_sort(v);
        EXPECT_EQ(std::is_sorted(v.begin(),v.end()),true) ;
    }


}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
