# SET9_a1_KimSD

## Отчет - set9_a1.pdf

## Реализованные алгоритмы

- MergeSort
- QuickSort
- StringMergeSort
- StringQuickSort
- MSD Radix Sort
- MSD Radix Sort + StringQuickSort

## Данные эксперимента

Исходные результаты замеров: `a1_all_results.csv`

Графики находятся в папке: `graphs/`

## Сборка и запуск

```bash

cd src

g++ -std=c++20 -O2 main.cpp StringGenerator.cpp StringSortTester.cpp StandardSorts.cpp StringMergeSort.cpp StringQuickSort.cpp MsdRadixSort.cpp MsdRadixQuickSort.cpp -o a1_experiment

./a1_experiment
