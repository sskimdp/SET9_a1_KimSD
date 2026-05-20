#ifndef STRING_SORT_TESTER_H
#define STRING_SORT_TESTER_H

#include "SortStatistics.h"

#include <string>
#include <vector>
#include <functional>
#include <fstream>

using namespace std;

class StringSortTester {
private:
    int runsCount;

public:
    explicit StringSortTester(int runsCount = 5);

    SortStatistics testAlgorithm(
        const vector<string>& originalArray,
        const function<void(vector<string>&, long long&)>& sortingFunction
    );

    bool isAlgorithmCorrect(
        const vector<string>& originalArray,
        const function<void(vector<string>&, long long&)>& sortingFunction
    );

    void printResultLine(
        const string& arrayType,
        int size,
        const string& algorithmName,
        const SortStatistics& statistics
    );

    void writeCsvLine(
        ofstream& csv,
        const string& arrayType,
        int size,
        const string& algorithmName,
        const SortStatistics& statistics
    );
};

#endif