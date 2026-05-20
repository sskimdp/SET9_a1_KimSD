#include <iostream>
#include <vector>
#include <string>

using namespace std;

class StringQuickSorter {
private:
    static int charAt(const string& value, int depth) {
        if (depth >= static_cast<int>(value.size())) {
            return -1;
        }

        return static_cast<unsigned char>(value[depth]);
    }

    static void stringQuickSortRecursive(
        vector<string>& array,
        int left,
        int right,
        int depth
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

            if (currentChar < pivotChar) {
                swap(array[less], array[i]);
                ++less;
                ++i;
            } else if (currentChar > pivotChar) {
                swap(array[i], array[greater]);
                --greater;
            } else {
                ++i;
            }
        }

        stringQuickSortRecursive(array, left, less - 1, depth);

        if (pivotChar >= 0) {
            stringQuickSortRecursive(array, less, greater, depth + 1);
        }

        stringQuickSortRecursive(array, greater + 1, right, depth);
    }

public:
    static void sortSubarray(
        vector<string>& array,
        int left,
        int right,
        int depth
    ) {
        if (left >= right) {
            return;
        }

        stringQuickSortRecursive(array, left, right, depth);
    }
};

class MsdRadixQuickSorter {
private:
    static constexpr int ALPHABET_SIZE = 256;
    static constexpr int ORIGINAL_ALPHABET_SIZE = 74;
    static constexpr int END_OF_STRING = 0;

    static int charAt(const string& value, int depth) {
        if (depth >= static_cast<int>(value.size())) {
            return END_OF_STRING;
        }

        return static_cast<unsigned char>(value[depth]) + 1;
    }

    static void msdRadixQuickSortRecursive(
        vector<string>& array,
        vector<string>& buffer,
        int left,
        int right,
        int depth
    ) {
        if (left >= right) {
            return;
        }

        int currentSize = right - left + 1;

        if (currentSize < ORIGINAL_ALPHABET_SIZE) {
            StringQuickSorter::sortSubarray(array, left, right, depth);
            return;
        }

        vector<int> count(ALPHABET_SIZE + 2, 0);

        for (int i = left; i <= right; ++i) {
            int currentChar = charAt(array[i], depth);
            ++count[currentChar + 1];
        }

        for (int r = 0; r < ALPHABET_SIZE + 1; ++r) {
            count[r + 1] += count[r];
        }

        vector<int> start = count;

        for (int i = left; i <= right; ++i) {
            int currentChar = charAt(array[i], depth);
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
                    depth + 1
                );
            }
        }
    }

public:
    static void sort(vector<string>& array) {
        if (array.size() <= 1) {
            return;
        }

        vector<string> buffer(array.size());

        msdRadixQuickSortRecursive(
            array,
            buffer,
            0,
            static_cast<int>(array.size()) - 1,
            0
        );
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

    MsdRadixQuickSorter::sort(array);

    for (const string& value : array) {
        cout << value << '\n';
    }

    return 0;
}