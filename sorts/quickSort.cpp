//
// Created by Jason on 5/10/2017.
//

#include <random>
#include "headers/sorts.h"


using std::random_device;
using std::mt19937_64;
using std::uniform_int_distribution;

/// The partition function which split and rearrange list[start, end]
/// into L[start, pivot] and R[pivot+1, end]
/// \param list The array to be partitioned
/// \param startIndex The array's start index
/// \param endIndex The array's end index.
/// \return The index of the pivot which splits the array.
static int partition(int list[], int startIndex, int endIndex) {
    // the pivot value
    int p = list[endIndex];
    // the index position that will be returned as the index of the pivot
    int i = startIndex - 1;
    for (int j = startIndex; j < endIndex; ++j) {
        if (list[j] <= p) {
            i++;
            // guarantee that the element <= p stays at the left hand side of p.
            // swap [i], [j]
            int tmp = list[i];
            list[i] = list[j];
            list[j] = tmp;
        }
    }
    // last step: now i is the position where the last element which is <= p,
    // so [i+1] > p, then swap [i+1] and [endIndex] ([endIndex] == p)
    list[endIndex] = list[i + 1];
    list[i + 1] = p;
    return i + 1;
}

/// Random sampling.
/// Instead of always partitioning using A[r], randomly swap A[r] w/ an element of A[p..r] first.
/// \param list The array to be partitioned
/// \param startIndex The array's start index
/// \param endIndex The array's end index.
/// \return The index of the pivot which splits the array.
static int randomizedPartion(int list[], int startIndex, int endIndex) {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<int> dist(startIndex, endIndex);
    int r = dist(gen);
    // swap list[r] and list[endIndex]
    int tmp = list[r];
    list[r] = list[endIndex];
    list[endIndex] = tmp;
    return partition(list, startIndex, endIndex);
}

/// The quick sort inner helper function
/// \param list The array to be sorted.
/// \param startIndex The start index of the array.
/// \param endIndex The end index of the array.
static void innerQuickSort(int list[], int startIndex, int endIndex) {
    // the base case - it's already sorted
    if (startIndex >= endIndex) return;
    int pivotIndex = randomizedPartion(list, startIndex, endIndex);
    // the left sub-array:
    innerQuickSort(list, startIndex, pivotIndex - 1);
    // the right sub-array
    innerQuickSort(list, pivotIndex + 1, endIndex);
}

/// Quick sort implementation
/// \param list The array to be sorted
/// \param size The length of the array
void quickSort(int list[], int size) {
    innerQuickSort(list, 0, size - 1);
}
