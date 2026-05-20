#include "StringSortTester.h"

#include <iostream>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;

StringSortTester::StringSortTester(int runsCount)
    : runsCount(runsCount) {}

SortStatistics StringSortTester::testAlgorithm(
    const vector<string>& originalArray,
    const function<void(vector<string>&, long long&)>& sortingFunction
) {
    long long totalOperations = 0;
    double totalTime = 0.0;

    for (int run = 0; run < runsCount; ++run) {
        vector<string> array = originalArray;
        long long charOperations = 0;

        auto start = chrono::high_resolution_clock::now();

        sortingFunction(array, charOperations);

        auto finish = chrono::high_resolution_clock::now();

        chrono::duration<double, micro> elapsed = finish - start;

        totalTime += elapsed.count();
        totalOperations += charOperations;
    }

    return {
        totalTime / runsCount,
        totalOperations / runsCount
    };
}

bool StringSortTester::isAlgorithmCorrect(
    const vector<string>& originalArray,
    const function<void(vector<string>&, long long&)>& sortingFunction
) {
    vector<string> array = originalArray;
    vector<string> expected = originalArray;

    long long charOperations = 0;

    sortingFunction(array, charOperations);
    sort(expected.begin(), expected.end());

    return array == expected;
}

void StringSortTester::printResultLine(
    const string& arrayType,
    int size,
    const string& algorithmName,
    const SortStatistics& statistics
) {
    cout << left << setw(25) << arrayType
         << setw(10) << size
         << setw(25) << algorithmName
         << setw(20) << fixed << setprecision(2) << statistics.averageTimeMicroseconds
         << setw(25) << statistics.averageCharOperations
         << '\n';
}

void StringSortTester::writeCsvLine(
    ofstream& csv,
    const string& arrayType,
    int size,
    const string& algorithmName,
    const SortStatistics& statistics
) {
    csv << arrayType << ','
        << size << ','
        << algorithmName << ','
        << fixed << setprecision(2) << statistics.averageTimeMicroseconds << ','
        << statistics.averageCharOperations
        << '\n';
}