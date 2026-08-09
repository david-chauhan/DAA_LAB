# Merge Sort Comparison: 2-Way vs 3-Way

## Overview

This project compares **2-way Merge Sort** and **3-way Merge Sort** by
counting the number of element comparisons performed for different input
sizes.

The program generates random integer arrays, sorts the same input using
both algorithms, and records the comparison counts in a CSV file.

## Algorithms

### 1. 2-Way Merge Sort

The standard Merge Sort algorithm divides the array into two
approximately equal parts.

-   Divides the array into **2 subarrays**
-   Recursively sorts both halves
-   Merges the two sorted halves
-   Time Complexity: **O(n log n)**
-   Extra Space: **O(n)**

### 2. 3-Way Merge Sort

The 3-way version divides the array into three approximately equal
parts.

-   Divides the array into **3 subarrays**
-   Recursively sorts all three parts
-   Merges the three sorted parts
-   Time Complexity: **O(n log n)**
-   Extra Space: **O(n)**

Although both algorithms have the same asymptotic time complexity, their
actual number of comparisons can differ because the merging process is
different.

## Files

``` text
.
├── mergesort.c
├── mergesort_data.csv
└── README.md
```

### `mergesort.c`

Contains the complete implementation of:

-   `mergesort2()` --- 2-way Merge Sort
-   `merge2()` --- 2-way merge
-   `mergesort3()` --- 3-way Merge Sort
-   `merge3()` --- 3-way merge
-   Random input generation
-   Comparison counting
-   CSV output generation

### `mergesort_data.csv`

Contains the experimental results in the following format:

``` text
n,mergesort2_comparisons,mergesort3_comparisons
```

## Input Sizes

The program tests the following array sizes:

``` text
100
500
1000
5000
10000
50000
100000
500000
```

For every size:

1.  A random array is generated.
2.  The array is copied to a working array.
3.  2-way Merge Sort is executed.
4.  The number of comparisons is recorded.
5.  The original random data is copied again.
6.  3-way Merge Sort is executed.
7.  Its comparison count is recorded.
8.  Results are printed and saved to the CSV file.

Using the same original array for both algorithms makes the comparison
more consistent.

## How Comparison Counting Works

A global variable is used:

``` c
long comparisons;
```

Every time the algorithm compares two or more array elements, the
counter is increased.

For example, in the 2-way merge:

``` c
comparisons++;

if (arr[i] <= arr[j])
    tmp[k++] = arr[i++];
else
    tmp[k++] = arr[j++];
```

For the 3-way merge, the main three-way selection may require two
comparisons:

``` c
comparisons += 2;
```

Therefore, the reported values represent the number of
**element-to-element comparisons**, not the number of loop iterations.

## Compilation

Using GCC:

``` bash
gcc mergesort.c -o mergesort
```

## Run

### Windows

``` bash
mergesort.exe
```

### Linux / macOS

``` bash
./mergesort
```

After execution, the program creates:

``` text
mergesort_data.csv
```

## Expected Output Format

The terminal output has the following structure:

``` text
       n | 2-way (halves)        | 3-way (thirds)
     100 | ...                   | ...
     500 | ...                   | ...
    1000 | ...                   | ...
```

The exact values can change because the input array is generated using
`rand()`.

## Complexity Analysis

  Algorithm          Divide    Merge   Overall
  ------------------ --------- ------- ------------
  2-way Merge Sort   2 parts   O(n)    O(n log n)
  3-way Merge Sort   3 parts   O(n)    O(n log n)

### 2-Way Merge Sort

The recurrence is approximately:

``` text
T(n) = 2T(n/2) + O(n)
```

Therefore:

``` text
T(n) = O(n log n)
```

### 3-Way Merge Sort

The recurrence is approximately:

``` text
T(n) = 3T(n/3) + O(n)
```

Therefore:

``` text
T(n) = O(n log n)
```

The logarithm has a different base, but changing the logarithm's base
only changes the constant factor.

## Important Observation

3-way Merge Sort does **not automatically mean fewer comparisons**.

During a 2-way merge, the algorithm compares two current elements.

During the main part of a 3-way merge, the implementation may need up to
two comparisons to determine which of the three current elements is
smallest.

Thus, even though both algorithms are **O(n log n)**, the practical
comparison count depends on the merge implementation and the input.

## Experimental Result

The program produces a CSV file that can be imported into:

-   Excel
-   Google Sheets
-   Python
-   MATLAB
-   R
-   Other data-analysis tools

The CSV can be used to create a graph of:

``` text
Array Size (n) vs Number of Comparisons
```

This makes it possible to experimentally compare the growth of 2-way and
3-way Merge Sort.

## Notes

-   The random values are generated using `rand()`.
-   `srand(time(NULL))` is used to initialize the random seed.
-   The program uses dynamically allocated memory.
-   The same random input is used for both algorithms at each `n`.
-   The temporary array is reused during recursive calls.
-   The comparison counter is reset before each sorting algorithm.

## Conclusion

Both 2-way and 3-way Merge Sort have an asymptotic time complexity of:

**O(n log n)**

However, asymptotic complexity does not tell the complete story. The
number of comparisons performed during merging can differ significantly
between the two approaches.

This experiment provides a practical way to observe the difference
between the two implementations using actual comparison counts.

## Author

**Data Structures & Algorithms / Algorithm Analysis Lab**
