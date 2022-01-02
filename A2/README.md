# PP

## How to compine & run?

```console
gcc -g -Wall -o pth_pi_mutex pth_pi_mutex.c -lm -lpthread
./pth_pi_mutex <number of threads> <n>
```

1. n is the number of terms of the Maclaurin series to use
2. n should be evenly divisible by the number of threads

