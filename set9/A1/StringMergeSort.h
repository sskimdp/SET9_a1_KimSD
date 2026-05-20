#ifndef STRING_MERGE_SORT_H
#define STRING_MERGE_SORT_H

#include <string>
#include <vector>

using namespace std;

struct LcpCompareResult {
    int compareResult;
    int lcpLength;
};

struct StringWithLcp {
    string value;
    int lcpWithPrevious;
};

class StringMergeSort {
private:
    static LcpCompareResult lcpCompare(
        const string& first,
        const string& second,
        int knownPrefixLength,
        long long& charOperations
    );

    static vector<StringWithLcp> stringMerge(
        vector<StringWithLcp> leftPart,
        vector<StringWithLcp> rightPart,
        long long& charOperations
    );

    static vector<StringWithLcp> stringMergeSortRecursive(
        const vector<string>& array,
        int left,
        int right,
        long long& charOperations
    );

public:
    static void sort(vector<string>& array, long long& charOperations);
};

#endif