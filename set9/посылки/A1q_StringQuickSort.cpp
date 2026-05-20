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
    static void sort(vector<string>& array) {
        if (array.size() <= 1) {
            return;
        }

        stringQuickSortRecursive(
            array,
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

    StringQuickSorter::sort(array);

    for (const string& value : array) {
        cout << value << '\n';
    }

    return 0;
}