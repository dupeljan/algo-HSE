#ifndef QUICK_SORT_H
#define QUICK_SORT_H

void quick_sort(std::vector<int> &v);
int partitision_rand(std::vector<int> &v, int p, int r);
bool is_sorted(std::vector<int> v);

/*
 * Quick sort
 * params:
 *  std::vector<int> v - vector to be sorted
 *  p - left bound of vector
 *  r - right bound of vector
 */
void quick_sort(std::vector<int> &v, int p, int r)
{
    if(r <= p)
        return;

    auto i = partitision_rand(v, p, r);
    quick_sort(v, p, i-1);
    quick_sort(v, i+1, r);
}

void quick_sort(std::vector<int> &v)
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
int partitision_rand(std::vector<int> &v, int p, int r)
{
    // Random element choice
    auto i_rand = std::rand() % (r - p + 1) + p;
    std::swap(v[i_rand], v[r]);
    //
    auto x = v[r];
    int i = p - 1;
    for(int j = p; j < r; j++ )
    {
        if (v[j] <= x)
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
bool is_sorted(std::vector<int> v)
{
    bool res = true;
    for(auto x = v.begin(); (x+1) != v.end() && res; x++)
    {
        if( *x > *(x+1))
        {
            res = false;
        }
    }

    return res;
}
#endif // QUICK_SORT_H
