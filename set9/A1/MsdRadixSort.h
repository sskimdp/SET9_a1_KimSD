#ifndef MSD_RADIX_SORT_H
#define MSD_RADIX_SORT_H

#include <string>
#include <vector>

using namespace std;

class MsdRadixSort {
private:
    static constexpr int ALPHABET_SIZE = 256;
    static constexpr int END_OF_STRING = 0;

    static int charAt(
        const string& value,
        int depth,
        long long& charOperations
    );

    static void msdRadixSortRecursive(
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