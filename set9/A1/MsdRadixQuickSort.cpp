#include "MsdRadixQuickSort.h"
#include "StringQuickSort.h"

using namespace std;

int MsdRadixQuickSort::charAt(
    const string& value,
    int depth,
    long long& charOperations
) {
    ++charOperations;

    if (depth >= static_cast<int>(value.size())) {
        return END_OF_STRING;
    }

    return static_cast<unsigned char>(value[depth]) + 1;
}

void MsdRadixQuickSort::msdRadixQuickSortRecursive(
    vector<string>& array,
    vector<string>& buffer,
    int left,
    int right,
    int depth,
    long long& charOperations
) {
    if (left >= right) {
        return;
    }

    int currentSize = right - left + 1;

    if (currentSize < ORIGINAL_ALPHABET_SIZE) {
        StringQuickSort::sortSubarray(
            array,
            left,
            right,
            depth,
            charOperations
        );

        return;
    }

    vector<int> count(ALPHABET_SIZE + 2, 0);

    for (int i = left; i <= right; ++i) {
        int currentChar = charAt(array[i], depth, charOperations);
        ++count[currentChar + 1];
    }

    for (int r = 0; r < ALPHABET_SIZE + 1; ++r) {
        count[r + 1] += count[r];
    }

    vector<int> start = count;

    for (int i = left; i <= right; ++i) {
        int currentChar = charAt(array[i], depth, charOperations);
        buffer[left + count[currentChar]] = array[i];
        ++count[currentChar];
    }

    for (int i = left; i <= right; ++i) {
        array[i] = buffer[i];
    }

    for (int r = 1; r <= ALPHABET_SIZE; ++r) {
        int groupLeft = left + start[r];
        int groupRight = left + start[r + 1] - 1;

        if (groupLeft < groupRight) {
            msdRadixQuickSortRecursive(
                array,
                buffer,
                groupLeft,
                groupRight,
                depth + 1,
                charOperations
            );
        }
    }
}

void MsdRadixQuickSort::sort(vector<string>& array, long long& charOperations) {
    if (array.size() <= 1) {
        return;
    }

    vector<string> buffer(array.size());

    msdRadixQuickSortRecursive(
        array,
        buffer,
        0,
        static_cast<int>(array.size()) - 1,
        0,
        charOperations
    );
}