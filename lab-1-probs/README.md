Q1 : Average number of steps required for a binary search with 1024 entries:
Max = 11 ( log2(N) + 1)
Average : 9.01172


Q2) In this exercise, we will compare the performance of arrays and vectors.
Average of local array: 9.72735
Average of pre-allocated array: 6.96443
Average of local vector: 144.435
Average of local vector with reserve: 96.0555
Average of local vector with iterator: 167.056
Average of Globally declared static vector: 75.0583

Q3) // Let's consider vectors again. When a vector is declared without specifying
// a size, it starts empty. However, there needs to be some initial allocation
// of space in anticipation of new elements being added. As we begin filling
// the vector, there will come a point when the allocated memory runs out.
// At this stage, the vector needs to allocate more memory. Your task is to
// write code that detects at what size the new allocation occurs and determine
// the amount of extra memory being allocated.

Presented in plot.png
