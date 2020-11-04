#ifndef TEST_H
#define TEST_H
#include "quick_sort.h"

/*
 * Test quick sort
 */
bool test_quick_sort()
{
    bool res = true;

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
        res &= is_sorted(v);
    }

    return res;
}
#endif // TEST_H
