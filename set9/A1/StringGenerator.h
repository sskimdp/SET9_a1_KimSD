#ifndef STRING_GENERATOR_H
#define STRING_GENERATOR_H

#include <string>
#include <vector>
#include <random>

using namespace std;

class StringGenerator {
private:
    static constexpr int MIN_LENGTH = 10;
    static constexpr int MAX_LENGTH = 200;
    static constexpr int MAX_ARRAY_SIZE = 3000;

    string alphabet;
    mt19937 generator;

    int randomInt(int left, int right);
    char randomChar();

public:
    StringGenerator();

    string generateRandomString();

    vector<string> generateRandomArray(int size);
    vector<string> generateSortedArray(int size);
    vector<string> generateReverseSortedArray(int size);
    vector<string> generateAlmostSortedArray(int size);
    vector<string> generateArrayWithCommonPrefixes(int size);

    vector<string> getSubarray(const vector<string>& source, int size);

    vector<int> generateSizes();

    vector<string> generateMaxRandomArray();
    vector<string> generateMaxReverseSortedArray();
    vector<string> generateMaxAlmostSortedArray();
    vector<string> generateMaxCommonPrefixArray();
};

#endif