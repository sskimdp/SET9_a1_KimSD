#ifndef STRING_QUICK_SORT_H
#define STRING_QUICK_SORT_H

#include <string>
#include <vector>

using namespace std;

class StringQuickSort {
private:
    static int charAt(const string& value, int depth);

    static bool lessThan(
        int firstChar,
        int secondChar,
        long long& charOperations
    );

    static bool greaterThan(
        int firstChar,
        int secondChar,
        long long& charOperations
    );

    static void stringQuickSortRecursive(
        vector<string>& array,
        int left,
        int right,
        int depth,
        long long& charOperations
    );

public:
    static void sort(vector<string>& array, long long& charOperations);

    static void sortSubarray(
        vector<string>& array,
        int left,
        int right,
        int depth,
        long long& charOperations
    );
};

#endif