# PP

## How to compile & run?

```console
gcc -g -Wall -o pthread_matrix pthread_matrix.c -lm -lpthread
./pthread_matrix <number of threads> <m> <n> <k>
```

1. m - number of rows 
2. n - number of columns
3. k - number of iterations

Example: ./pthread_matrix 3 5 7 6

## Execution time

K = 1

| Threads           | 1             | 5             | 15            | 20            | 
| ----------------- | ------------- | ------------- | ------------- | ------------- | 
| Matrix: 5 x 5     | 1.511574e-04  | 2.789497e-04  | 5.941391e-04  | 6.980896e-04  |               
| Matrix: 10 x 10   | 1.330376e-04  | 4.661083e-04  | 1.988173e-03  | 1.023054e-03  |      
| Matrix: 25 x 25   | 2.508163e-04  | 6.639957e-04  | 1.697063e-03  | 2.868891e-03  |      
| Matrix: 50 x 50   | 4.189014e-04  | 2.011061e-03  | 4.714966e-03  | 8.265018e-03  |      

K = 25

| Threads           | 1             | 5             | 15            | 25            | 35            |
| ----------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
| Matrix: 5 x 5     | 1.540184e-04  | 3.550053e-04  | 1.121044e-03  | 1.123905e-03  | 1.884937e-03  |          
| Matrix: 10 x 10   | 3.359318e-04  | 1.707077e-03  | 3.437042e-03  | 3.713846e-03  | 4.837036e-03  |
| Matrix: 25 x 25   | 1.492977e-03  | 7.202864e-03  | 1.264191e-02  | 1.444602e-02  | 1.686502e-02  |
| Matrix: 50 x 50   | 3.552914e-03  | 2.561498e-02  | 3.879499e-02  | 4.613805e-02  | 5.691695e-02  |

K = 50

| Threads           | 1             | 5             | 15            | 25            | 35            |
| ----------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
| Matrix: 5 x 5     | 2.379417e-04  | 6.639957e-04  | 2.016068e-03  | 2.769947e-03  | 2.667904e-03  |          
| Matrix: 10 x 10   | 5.609989e-04  | 2.096176e-03  | 4.791021e-03  | 6.857157e-03  | 9.034157e-03  |
| Matrix: 25 x 25   | 1.883984e-03  | 1.207399e-02  | 2.062798e-02  | 2.425385e-02  | 2.885199e-02  |
| Matrix: 50 x 50   | 7.604122e-03  | 5.031586e-02  | 7.721615e-02  | 8.207107e-02  | 9.933805e-02  |

## Implementation

Create the m x n matrix. We will use random numbers at margins, and the middle of the matrix will be initialized with zeros. 
In the second step, we will assign for each thread a number of columns on which it should operate. For example, for a 5 x 7 matrix with 3 threads, thread 1 will pick column 1 and 2, thread 2 will pick column 3 and 4, and given the fact that we have only one column left, thread 3 will pick only column 5.
The algorithm use one mutex which makes sure that the shared data is not being edited by multiple threads and one conditional variable which signal when the last item from the row was computed (for the last column assigned for the given thread) and wait until the element from its left is computed.
