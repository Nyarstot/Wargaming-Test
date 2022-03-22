#ifndef Q_SORT_H
#define Q_SORT_H

#include <utility>
#include <vector>

void q_Sort(int* arr, int left, int right)
{
    int l = left;
    int r = right;
    int pivot = arr[(l + r) / 2];

    while (l <= r) 
    {
        while (arr[l] < pivot) {
            l++;
        }
        while (arr[r] > pivot) {
            r--;
        }

        if (l <= r) {
            std::swap(arr[l], arr[r]);
            l++; r--;
        }
    }

    if (r > left) {
        q_Sort(arr, left, r);
    }
    if (l < right) {
        q_Sort(arr, l, right);
    }
}

#endif // !Q_SORT_H
