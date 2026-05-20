#ifndef STANDARD_SORTS_H
#define STANDARD_SORTS_H

#include <string>
#include <vector>

using namespace std;

class StandardSorts {
private:
    static bool lessOrEqual(
        const string& first,
        const string& second,
        long long& charOperations
    );

    static void mergeSortRecursive(
        vector<string>& array,
        vector<string>& buffer,
        int left,
        int right,
        long long& charOperations
    );

    static void merge(
        vector<string>& array,
        vector<string>& buffer,
        int left,
        int middle,
        int right,
        long long& charOperations
    );

    static void quickSortRecursive(
        vector<string>& array,
        int left,
        int right,
        long long& charOperations
    );

public:
    static int compareStrings(
        const string& first,
        const string& second,
        long long& charOperations
    );

    static void mergeSort(vector<string>& array, long long& charOperations);

    static void quickSort(vector<string>& array, long long& charOperations);
};

#endif