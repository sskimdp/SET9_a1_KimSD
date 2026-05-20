#include "StandardSorts.h"

#include <algorithm>

using namespace std;

bool StandardSorts::lessOrEqual(
    const string& first,
    const string& second,
    long long& charOperations
) {
    return compareStrings(first, second, charOperations) <= 0;
}

int StandardSorts::compareStrings(
    const string& first,
    const string& second,
    long long& charOperations
) {
    int minLength = min(static_cast<int>(first.size()), static_cast<int>(second.size()));

    for (int i = 0; i < minLength; ++i) {
        ++charOperations;

        if (first[i] < second[i]) {
            return -1;
        }

        if (first[i] > second[i]) {
            return 1;
        }
    }

    if (first.size() < second.size()) {
        return -1;
    }

    if (first.size() > second.size()) {
        return 1;
    }

    return 0;
}

void StandardSorts::mergeSort(vector<string>& array, long long& charOperations) {
    if (array.size() <= 1) {
        return;
    }

    vector<string> buffer(array.size());
    mergeSortRecursive(array, buffer, 0, static_cast<int>(array.size()) - 1, charOperations);
}

void StandardSorts::mergeSortRecursive(
    vector<string>& array,
    vector<string>& buffer,
    int left,
    int right,
    long long& charOperations
) {
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;

    mergeSortRecursive(array, buffer, left, middle, charOperations);
    mergeSortRecursive(array, buffer, middle + 1, right, charOperations);

    merge(array, buffer, left, middle, right, charOperations);
}

void StandardSorts::merge(
    vector<string>& array,
    vector<string>& buffer,
    int left,
    int middle,
    int right,
    long long& charOperations
) {
    int i = left;
    int j = middle + 1;
    int k = left;

    while (i <= middle && j <= right) {
        if (lessOrEqual(array[i], array[j], charOperations)) {
            buffer[k] = array[i];
            ++i;
        } else {
            buffer[k] = array[j];
            ++j;
        }

        ++k;
    }

    while (i <= middle) {
        buffer[k] = array[i];
        ++i;
        ++k;
    }

    while (j <= right) {
        buffer[k] = array[j];
        ++j;
        ++k;
    }

    for (int index = left; index <= right; ++index) {
        array[index] = buffer[index];
    }
}

void StandardSorts::quickSort(vector<string>& array, long long& charOperations) {
    if (array.size() <= 1) {
        return;
    }

    quickSortRecursive(array, 0, static_cast<int>(array.size()) - 1, charOperations);
}

void StandardSorts::quickSortRecursive(
    vector<string>& array,
    int left,
    int right,
    long long& charOperations
) {
    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;
    string pivot = array[left + (right - left) / 2];

    while (i <= j) {
        while (compareStrings(array[i], pivot, charOperations) < 0) {
            ++i;
        }

        while (compareStrings(array[j], pivot, charOperations) > 0) {
            --j;
        }

        if (i <= j) {
            swap(array[i], array[j]);
            ++i;
            --j;
        }
    }

    if (left < j) {
        quickSortRecursive(array, left, j, charOperations);
    }

    if (i < right) {
        quickSortRecursive(array, i, right, charOperations);
    }
}