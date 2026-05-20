#ifndef MSD_RADIX_QUICK_SORT_H
#define MSD_RADIX_QUICK_SORT_H

#include <string>
#include <vector>

using namespace std;

class MsdRadixQuickSort {
private:
    static constexpr int ALPHABET_SIZE = 256;
    static constexpr int ORIGINAL_ALPHABET_SIZE = 74;
    static constexpr int END_OF_STRING = 0;

    static int charAt(
        const string& value,
        int depth,
        long long& charOperations
    );

    static void msdRadixQuickSortRecursive(
        vector<string>& array,
        vector<string>& buffer,
        int left,
        int right,
        int depth,
        long long& charOperations
    );

public:
    static void sort(vector<string>& array, long long& charOperations);
};

#endif