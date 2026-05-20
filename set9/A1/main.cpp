#include "StringGenerator.h"
#include "StringSortTester.h"

#include "StandardSorts.h"
#include "StringMergeSort.h"
#include "StringQuickSort.h"
#include "MsdRadixSort.h"
#include "MsdRadixQuickSort.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <iomanip>

using namespace std;

int main() {
    StringGenerator generator;
    StringSortTester tester(5);

    vector<int> sizes = generator.generateSizes();

    vector<string> maxRandomArray = generator.generateMaxRandomArray();
    vector<string> maxReverseSortedArray = generator.generateMaxReverseSortedArray();
    vector<string> maxAlmostSortedArray = generator.generateMaxAlmostSortedArray();
    vector<string> maxCommonPrefixArray = generator.generateMaxCommonPrefixArray();

    vector<pair<string, function<void(vector<string>&, long long&)>>> algorithms = {
        {"MergeSort", StandardSorts::mergeSort},
        {"QuickSort", StandardSorts::quickSort},
        {"StringMergeSort", StringMergeSort::sort},
        {"StringQuickSort", StringQuickSort::sort},
        {"MsdRadixSort", MsdRadixSort::sort},
        {"MsdRadixQuickSort", MsdRadixQuickSort::sort}
    };

    ofstream csv("a1_all_results.csv");

    if (!csv.is_open()) {
        cerr << "Error: could not create CSV file.\n";
        return 1;
    }

    csv << "array_type,size,algorithm,time_microseconds,char_operations\n";

    cout << left << setw(25) << "Array type"
         << setw(10) << "Size"
         << setw(25) << "Algorithm"
         << setw(20) << "Time, microsec"
         << setw(25) << "Char operations"
         << '\n';

    cout << string(105, '-') << '\n';

    for (int size : sizes) {
        vector<pair<string, vector<string>>> testArrays = {
            {"Random", generator.getSubarray(maxRandomArray, size)},
            {"Reverse sorted", generator.getSubarray(maxReverseSortedArray, size)},
            {"Almost sorted", generator.getSubarray(maxAlmostSortedArray, size)},
            {"Common prefixes", generator.getSubarray(maxCommonPrefixArray, size)}
        };

        for (const auto& testArray : testArrays) {
            const string& arrayType = testArray.first;
            const vector<string>& array = testArray.second;

            for (const auto& algorithm : algorithms) {
                const string& algorithmName = algorithm.first;
                const auto& sortingFunction = algorithm.second;

                if (!tester.isAlgorithmCorrect(array, sortingFunction)) {
                    cerr << "Error: " << algorithmName
                         << " sorted array incorrectly. Array type: "
                         << arrayType << ", size: " << size << '\n';

                    csv.close();
                    return 1;
                }

                SortStatistics statistics = tester.testAlgorithm(array, sortingFunction);

                tester.printResultLine(arrayType, size, algorithmName, statistics);
                tester.writeCsvLine(csv, arrayType, size, algorithmName, statistics);
            }

            cout << string(105, '-') << '\n';
        }
    }

    csv.close();

    cout << "\nResults were saved to a1_all_results.csv\n";

    return 0;
}