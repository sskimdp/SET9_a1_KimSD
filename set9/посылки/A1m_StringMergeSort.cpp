#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct LcpCompareResult {
    int compareResult;
    int lcpLength;
};

struct StringWithLcp {
    string value;
    int lcpWithPrevious;
};

class StringMergeSorter {
private:
    static LcpCompareResult lcpCompare(
        const string& first,
        const string& second,
        int knownPrefixLength
    ) {
        int i = knownPrefixLength;

        int firstLength = static_cast<int>(first.size());
        int secondLength = static_cast<int>(second.size());
        int minLength = min(firstLength, secondLength);

        while (i < minLength) {
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

    static vector<StringWithLcp> stringMerge(
        vector<StringWithLcp> leftPart,
        vector<StringWithLcp> rightPart
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
                    knownPrefixLength
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

    static vector<StringWithLcp> stringMergeSortRecursive(
        const vector<string>& array,
        int left,
        int right
    ) {
        if (left == right) {
            return {{array[left], 0}};
        }

        int middle = left + (right - left) / 2;

        vector<StringWithLcp> leftPart = stringMergeSortRecursive(array, left, middle);
        vector<StringWithLcp> rightPart = stringMergeSortRecursive(array, middle + 1, right);

        return stringMerge(leftPart, rightPart);
    }

public:
    static void sort(vector<string>& array) {
        if (array.size() <= 1) {
            return;
        }

        vector<StringWithLcp> sortedWithLcp = stringMergeSortRecursive(
            array,
            0,
            static_cast<int>(array.size()) - 1
        );

        for (int i = 0; i < static_cast<int>(array.size()); ++i) {
            array[i] = sortedWithLcp[i].value;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> array(n);

    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }

    StringMergeSorter::sort(array);

    for (const string& value : array) {
        cout << value << '\n';
    }

    return 0;
}