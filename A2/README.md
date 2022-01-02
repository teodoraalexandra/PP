# PP

## How to compine & run?

```console
gcc -g -Wall -o pthread_matrix pthread_matrix.c -lm -lpthread
./pthread_matrix <number of threads> <m> <n> <k>
```

1. m - number of rows 
2. n - number of columns
3. k - number of iterations

Example: ./pthread_matrix 3 5 7 6

