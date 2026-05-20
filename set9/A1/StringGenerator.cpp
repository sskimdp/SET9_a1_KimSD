#include "StringGenerator.h"

#include <algorithm>

using namespace std;

int StringGenerator::randomInt(int left, int right) {
    uniform_int_distribution<int> distribution(left, right);
    return distribution(generator);
}

char StringGenerator::randomChar() {
    int index = randomInt(0, static_cast<int>(alphabet.size()) - 1);
    return alphabet[index];
}

StringGenerator::StringGenerator()
    : alphabet("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
               "abcdefghijklmnopqrstuvwxyz"
               "0123456789"
               "!@#%:;^&*()-"),
      generator(random_device{}()) {}

string StringGenerator::generateRandomString() {
    int length = randomInt(MIN_LENGTH, MAX_LENGTH);

    string result;
    result.reserve(length);

    for (int i = 0; i < length; ++i) {
        result.push_back(randomChar());
    }

    return result;
}

vector<string> StringGenerator::generateRandomArray(int size) {
    vector<string> result;
    result.reserve(size);

    for (int i = 0; i < size; ++i) {
        result.push_back(generateRandomString());
    }

    return result;
}

vector<string> StringGenerator::generateSortedArray(int size) {
    vector<string> result = generateRandomArray(size);
    sort(result.begin(), result.end());
    return result;
}

vector<string> StringGenerator::generateReverseSortedArray(int size) {
    vector<string> result = generateSortedArray(size);
    reverse(result.begin(), result.end());
    return result;
}

vector<string> StringGenerator::generateAlmostSortedArray(int size) {
    vector<string> result = generateSortedArray(size);

    int swapsCount = max(1, size / 20);

    for (int i = 0; i < swapsCount; ++i) {
        int firstIndex = randomInt(0, size - 1);
        int secondIndex = randomInt(0, size - 1);
        swap(result[firstIndex], result[secondIndex]);
    }

    return result;
}

vector<string> StringGenerator::generateArrayWithCommonPrefixes(int size) {
    vector<string> prefixes = {
        "abc",
        "test",
        "prefix",
        "sort",
        "string",
        "common",
        "data",
        "algorithm"
    };

    vector<string> result;
    result.reserve(size);

    for (int i = 0; i < size; ++i) {
        string prefix = prefixes[randomInt(0, static_cast<int>(prefixes.size()) - 1)];

        int totalLength = randomInt(MIN_LENGTH, MAX_LENGTH);
        string current = prefix;

        while (static_cast<int>(current.size()) < totalLength) {
            current.push_back(randomChar());
        }

        result.push_back(current);
    }

    return result;
}

vector<string> StringGenerator::getSubarray(const vector<string>& source, int size) {
    return vector<string>(source.begin(), source.begin() + size);
}

vector<int> StringGenerator::generateSizes() {
    vector<int> sizes;

    for (int size = 100; size <= MAX_ARRAY_SIZE; size += 100) {
        sizes.push_back(size);
    }

    return sizes;
}

vector<string> StringGenerator::generateMaxRandomArray() {
    return generateRandomArray(MAX_ARRAY_SIZE);
}

vector<string> StringGenerator::generateMaxReverseSortedArray() {
    return generateReverseSortedArray(MAX_ARRAY_SIZE);
}

vector<string> StringGenerator::generateMaxAlmostSortedArray() {
    return generateAlmostSortedArray(MAX_ARRAY_SIZE);
}

vector<string> StringGenerator::generateMaxCommonPrefixArray() {
    return generateArrayWithCommonPrefixes(MAX_ARRAY_SIZE);
}