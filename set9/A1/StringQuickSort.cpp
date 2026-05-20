#include "StringQuickSort.h"

#include <algorithm>

using namespace std;

int StringQuickSort::charAt(const string& value, int depth) {
    if (depth >= static_cast<int>(value.size())) {
        return -1;
    }

    return static_cast<unsigned char>(value[depth]);
}

bool StringQuickSort::lessThan(
    int firstChar,
    int secondChar,
    long long& charOperations
) {
    ++charOperations;
    return firstChar < secondChar;
}

bool StringQuickSort::greaterThan(
    int firstChar,
    int secondChar,
    long long& charOperations
) {
    ++charOperations;
    return firstChar > secondChar;
}

void StringQuickSort::stringQuickSortRecursive(
    vector<string>& array,
    int left,
    int right,
    int depth,
    long long& charOperations
) {
    if (left >= right) {
        return;
    }

    int pivotIndex = left + (right - left) / 2;
    swap(array[left], array[pivotIndex]);

    int less = left;
    int greater = right;

    int pivotChar = charAt(array[left], depth);
    int i = left + 1;

    while (i <= greater) {
        int currentChar = charAt(array[i], depth);

        if (lessThan(currentChar, pivotChar, charOperations)) {
            swap(array[less], array[i]);
            ++less;
            ++i;
        } else if (greaterThan(currentChar, pivotChar, charOperations)) {
            swap(array[i], array[greater]);
            --greater;
        } else {
            ++i;
        }
    }

    stringQuickSortRecursive(array, left, less - 1, depth, charOperations);

    if (pivotChar >= 0) {
        stringQuickSortRecursive(array, less, greater, depth + 1, charOperations);
    }

    stringQuickSortRecursive(array, greater + 1, right, depth, charOperations);
}

void StringQuickSort::sort(vector<string>& array, long long& charOperations) {
    if (array.size() <= 1) {
        return;
    }

    stringQuickSortRecursive(
        array,
        0,
        static_cast<int>(array.size()) - 1,
        0,
        charOperations
    );
}

void StringQuickSort::sortSubarray(
    vector<string>& array,
    int left,
    int right,
    int depth,
    long long& charOperations
) {
    if (left >= right) {
        return;
    }

    stringQuickSortRecursive(array, left, right, depth, charOperations);
}