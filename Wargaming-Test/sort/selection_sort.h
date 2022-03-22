#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <utility>

void selection_sort(int* arr, int size)
{
    int i, imin;
    int j;

    for (i = 0; i < size; i++) {
        imin = i;
        for (j = (i + 1); j < size; j++) {
            if (arr[j] < arr[imin]) {
                imin = j;
            }
        }
        std::swap(arr[i], arr[imin]);
    }
}

#endif // !SELECTION_SORT_H
