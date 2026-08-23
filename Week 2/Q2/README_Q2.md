# Merge Sort vs Modified 3-Way Merge Sort

## Q2: Experimental Comparison

This project compares the standard **2-way Merge Sort** with a modified
**3-way Merge Sort** by measuring the number of element comparisons for
different input sizes.

Both algorithms have the theoretical time complexity:

**Θ(n log n)**

The experiment uses randomly generated integer arrays and counts the
comparisons performed during the sorting process.

------------------------------------------------------------------------

## Objective

The main objectives are:

-   Implement standard 2-way Merge Sort.
-   Implement modified 3-way Merge Sort.
-   Count the number of element comparisons.
-   Compare the practical performance of both algorithms.
-   Verify experimentally that both algorithms grow approximately as
    **Θ(n log n)**.
-   Plot comparisons against `n`.
-   Normalize the comparison count by `n log₂(n)` to check whether the
    ratio becomes approximately constant.

------------------------------------------------------------------------

## Algorithms

### 1. Standard Merge Sort --- 2-Way

The standard Merge Sort divides the array into two approximately equal
halves.

``` text
T(n) = 2T(n/2) + Θ(n)
```

Therefore:

``` text
T(n) = Θ(n log n)
```

The merge operation compares elements from two sorted subarrays.

### 2. Modified Merge Sort --- 3-Way

The modified version divides the array into three approximately equal
parts.

``` text
T(n) = 3T(n/3) + Θ(n)
```

Therefore:

``` text
T(n) = Θ(n log n)
```

The 3-way merge can require up to two element comparisons when selecting
the smallest element among the three current candidates.

------------------------------------------------------------------------

## Experimental Setup

The program generates a random array and runs both algorithms on the
**same input data** for each value of `n`.

Input sizes used:

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

For each input size:

1.  Generate a random array.
2.  Copy the original array into a working array.
3.  Run 2-way Merge Sort.
4.  Record the comparison count.
5.  Restore the original random input.
6.  Run 3-way Merge Sort.
7.  Record its comparison count.
8.  Store both results in a CSV file.

Using the same input for both algorithms makes the comparison fairer.

------------------------------------------------------------------------

## Comparison Counting

A global counter is used:

``` c
long comparisons;
```

In the 2-way merge, each comparison between two array elements
increments the counter:

``` c
comparisons++;

if (arr[i] <= arr[j])
    tmp[k++] = arr[i++];
else
    tmp[k++] = arr[j++];
```

In the main 3-way merge loop, two comparisons are counted:

``` c
comparisons += 2;
```

This is because determining the minimum of three candidates may require
two element-to-element comparisons.

------------------------------------------------------------------------

## Complexity Analysis

  -----------------------------------------------------------------------
  Algorithm        Number of     Merge Work           Time    Extra Space
                 Subproblems                    Complexity 
  ----------- -------------- -------------- -------------- --------------
  2-way Merge              2           Θ(n)     Θ(n log n)           Θ(n)
  Sort                                                     

  3-way Merge              3           Θ(n)     Θ(n log n)           Θ(n)
  Sort                                                     
  -----------------------------------------------------------------------

Although both algorithms have the same asymptotic complexity, the
constants can be different.

The 3-way merge performs more comparisons per selected element in its
main merge phase, so it can have a higher comparison count in practice.

------------------------------------------------------------------------

## Graph Analysis

### Comparisons vs `n`

The first graph plots:

``` text
Number of Comparisons vs n
```

The graph shows that the number of comparisons increases as `n`
increases.

The 3-way Merge Sort curve is above the 2-way Merge Sort curve for the
tested inputs, indicating that this particular 3-way implementation
performs more comparisons.

This does **not** contradict the theoretical result that both algorithms
are Θ(n log n). It indicates a difference in their constant factors.

### Ratio to `n log₂(n)`

The second graph plots:

``` text
comparisons / (n log₂(n))
```

For a Θ(n log n) algorithm, this ratio should approach or remain around
a constant as `n` becomes large.

The plotted ratios flatten toward approximately constant values,
supporting the conclusion that both algorithms have **Θ(n log n)**
growth.

The 3-way implementation has a larger constant factor than the 2-way
implementation in this experiment.

------------------------------------------------------------------------

## Why Both Are Θ(n log n)

### 2-Way Merge Sort

The recurrence is:

``` text
T(n) = 2T(n/2) + Θ(n)
```

At every recursion level, the total merge work is Θ(n), and there are
Θ(log n) levels.

Therefore:

``` text
T(n) = Θ(n log n)
```

### 3-Way Merge Sort

The recurrence is:

``` text
T(n) = 3T(n/3) + Θ(n)
```

Again, every recursion level performs Θ(n) total work, while the number
of levels is Θ(log n).

Therefore:

``` text
T(n) = Θ(n log n)
```

The base of the logarithm changes, but logarithms with different
constant bases differ only by a constant factor.

------------------------------------------------------------------------

## Files

``` text
.
├── mergesort.c
├── 2.csv(1).csv
├── 2graph(1).png
└── README.md
```

### `mergesort.c`

Contains the implementations of:

-   `merge2()`
-   `mergesort2()`
-   `merge3()`
-   `mergesort3()`
-   Random input generation
-   Comparison counting
-   CSV generation

### CSV Data

The CSV stores:

``` text
n,mergesort2_comparisons,mergesort3_comparisons
```

This data can be used to reproduce the graphs.

### Graph

The graph contains two plots:

1.  **Comparisons vs n**
2.  **Ratio to n log₂(n)**

------------------------------------------------------------------------

## Compilation

Using GCC:

``` bash
gcc mergesort.c -o mergesort
```

For a more strict compilation:

``` bash
gcc -Wall -Wextra -O2 mergesort.c -o mergesort
```

------------------------------------------------------------------------

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

------------------------------------------------------------------------

## Expected Terminal Output

The program prints results in this format:

``` text
       n | 2-way (halves)        | 3-way (thirds)
     100 | ...
     500 | ...
    1000 | ...
    5000 | ...
   10000 | ...
   50000 | ...
  100000 | ...
  500000 | ...

Data written to mergesort_data.csv
```

The exact comparison counts can vary because the input is generated
randomly using:

``` c
srand((unsigned) time(NULL));
```

------------------------------------------------------------------------

## Important Observation

The experiment demonstrates an important distinction between
**asymptotic complexity** and **actual operation counts**.

Both algorithms are:

``` text
Θ(n log n)
```

but the modified 3-way implementation can perform more comparisons
because selecting the minimum among three elements requires more
comparisons than selecting the minimum of two elements.

Therefore:

``` text
Same asymptotic complexity
        ≠
Same practical number of comparisons
```

The experiment shows that the 3-way version has a larger constant factor
for the comparison metric used here.

------------------------------------------------------------------------

## Conclusion

The experimental results support the theoretical analysis:

-   **2-way Merge Sort:** Θ(n log n)
-   **3-way Merge Sort:** Θ(n log n)
-   Both show approximately linearithmic growth.
-   The ratio `comparisons / (n log₂ n)` becomes relatively stable as
    `n` increases.
-   The modified 3-way implementation performs more comparisons than the
    standard 2-way implementation for the tested inputs.
-   Thus, although both algorithms have the same Big-Theta complexity,
    their practical constants differ.

This experiment demonstrates why experimental analysis is useful
alongside theoretical time-complexity analysis.

------------------------------------------------------------------------

## Author

**Data Structures & Algorithms / Algorithm Analysis Lab**
