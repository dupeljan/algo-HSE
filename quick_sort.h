#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include <math.h>

template<class T>
void quick_sort(std::vector<std::pair<double,T>> &v);
template<class T>
int partitision_rand(std::vector<std::pair<double,T>> &v, int p, int r);


/*
 * Compare two given intd
 * params:
 *          a, b - doubles to compare
 *          eps - comparison precision
 * return:
 *          true if a less than b
 *              else false
 */
template<class T>
bool cmp(std::pair<double,T> a, std::pair<double,T> b,double eps = 1e-5)
{
    return b.first - a.first > eps;
}

/*
 * Quick sort
 * sort by first element in pair
 * params:
 *  std::vector<int> v - vector to be sorted
 *  p - left bound of vector
 *  r - right bound of vector
 */
template<class T>
void quick_sort(std::vector<std::pair<double,T>> &v, int p, int r)
{
    if(r <= p)
        return;

    auto i = partitision_rand(v, p, r);
    quick_sort(v, p, i-1);
    quick_sort(v, i+1, r);
}

template<class T>
void quick_sort(std::vector<std::pair<double,T>> &v)
{
    quick_sort(v,0, v.size() - 1);
}

/*
 * Auxilarry function to quick sort.
 * Take first element and move each element less than first
 * elemet on left side  of first element in array order and move
 * each element more than first more on the right side of first
 * element
 * params:
 *  v - vector to make partition
 *  p - left bound of  part of vector
 *  r - right bound of  part of vector
 * returns:
 *  int - index of element partited by
 */
template<class T>
int partitision_rand(std::vector<std::pair<double,T>> &v, int p, int r)
{
    // Random element choice
    auto i_rand = std::rand() % (r - p + 1) + p;
    std::swap(v[i_rand], v[r]);
    //
    auto x = v[r];
    int i = p - 1;
    for(int j = p; j < r; j++ )
    {
        if (cmp(v[j], x))
        {
            i++;
            std::swap(v[i], v[j]);
        }
    }
    i++;
    std::swap(v[i], v[r]);
    return i;
}

/*
 * Test if vector is sorted from min to max value
 * params:
 *  v - vector to test
 * returns:
 *  bool - result of the test
 */
template<class T>
bool is_sorted(std::vector<std::pair<double,T>> v)
{
    bool res = true;
    for(auto x = v.begin(); (x+1) != v.end() && res; x++)
    {
        if(cmp(*(x+1),*x))
        {
            res = false;
        }
    }

    return res;
}

#endif // QUICK_SORT_H
