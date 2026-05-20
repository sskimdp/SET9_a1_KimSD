#include "StringMergeSort.h"

#include <algorithm>

using namespace std;

LcpCompareResult StringMergeSort::lcpCompare(
    const string& first,
    const string& second,
    int knownPrefixLength,
    long long& charOperations
) {
    int i = knownPrefixLength;

    int firstLength = static_cast<int>(first.size());
    int secondLength = static_cast<int>(second.size());
    int minLength = min(firstLength, secondLength);

    while (i < minLength) {
        ++charOperations;

        if (first[i] < second[i]) {
            return {-1, i};
        }

        if (first[i] > second[i]) {
            return {1, i};
        }

        ++i;
    }

    if (firstLength < secondLength) {
        return {-1, i};
    }

    if (firstLength > secondLength) {
        return {1, i};
    }

    return {0, i};
}

vector<StringWithLcp> StringMergeSort::stringMerge(
    vector<StringWithLcp> leftPart,
    vector<StringWithLcp> rightPart,
    long long& charOperations
) {
    vector<StringWithLcp> result;
    result.reserve(leftPart.size() + rightPart.size());

    int i = 0;
    int j = 0;

    int leftSize = static_cast<int>(leftPart.size());
    int rightSize = static_cast<int>(rightPart.size());

    while (i < leftSize && j < rightSize) {
        if (leftPart[i].lcpWithPrevious > rightPart[j].lcpWithPrevious) {
            result.push_back(leftPart[i]);
            ++i;
        } else if (leftPart[i].lcpWithPrevious < rightPart[j].lcpWithPrevious) {
            result.push_back(rightPart[j]);
            ++j;
        } else {
            int knownPrefixLength = leftPart[i].lcpWithPrevious;

            LcpCompareResult comparison = lcpCompare(
                leftPart[i].value,
                rightPart[j].value,
                knownPrefixLength,
                charOperations
            );

            if (comparison.compareResult <= 0) {
                result.push_back(leftPart[i]);
                ++i;

                if (j < rightSize) {
                    rightPart[j].lcpWithPrevious = comparison.lcpLength;
                }
            } else {
                result.push_back(rightPart[j]);
                ++j;

                if (i < leftSize) {
                    leftPart[i].lcpWithPrevious = comparison.lcpLength;
                }
            }
        }
    }

    while (i < leftSize) {
        result.push_back(leftPart[i]);
        ++i;
    }

    while (j < rightSize) {
        result.push_back(rightPart[j]);
        ++j;
    }

    if (!result.empty()) {
        result[0].lcpWithPrevious = 0;
    }

    return result;
}

vector<StringWithLcp> StringMergeSort::stringMergeSortRecursive(
    const vector<string>& array,
    int left,
    int right,
    long long& charOperations
) {
    if (left == right) {
        return {{array[left], 0}};
    }

    int middle = left + (right - left) / 2;

    vector<StringWithLcp> leftPart = stringMergeSortRecursive(
        array,
        left,
        middle,
        charOperations
    );

    vector<StringWithLcp> rightPart = stringMergeSortRecursive(
        array,
        middle + 1,
        right,
        charOperations
    );

    return stringMerge(leftPart, rightPart, charOperations);
}

void StringMergeSort::sort(vector<string>& array, long long& charOperations) {
    if (array.size() <= 1) {
        return;
    }

    vector<StringWithLcp> sortedWithLcp = stringMergeSortRecursive(
        array,
        0,
        static_cast<int>(array.size()) - 1,
        charOperations
    );

    for (int i = 0; i < static_cast<int>(array.size()); ++i) {
        array[i] = sortedWithLcp[i].value;
    }
}