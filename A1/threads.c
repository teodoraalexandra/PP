#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <pthread.h>

using namespace std;
int list[5][12];
int rows = 5;
int cols = 12;
int threadc;

void *threadf(void *arg)
{
    cout << endl;
    int x = *((int*)arg);
    for(int i = (x*60)/threadc; i < ((x+1) * 60)/threadc; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            if (list[i][j] % 2 == 0)
                list[i][j] += 1;
            else
                list[i][j] -= 1;
        }
    }
    pthread_exit(NULL);
}

void cArray()
{
    srand(time(NULL));
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            list[i][j] = rand() % 99 + 1;
        }
    }

}

void pArray(int list[][12], int rows, int cols)
{
    cout << "\n";
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cout << list[i][j] << " ";
        }
        cout << "\n";
    }
 }

int main(int argc, char *argv[])
{
    if(argc != 2) exit(0);
    threadc = atoi(argv[1]);
    assert(threadc >= 2 && threadc <=4);
    pthread_t *thread;
    int *data = new int[threadc];
    if(thread == NULL)
        exit(0);
    cArray();
    cout << "2-d Array: ";
    pArray(list, rows, cols);
    int t;
    for(int i = 0; i < threadc; i++)
    {
        data[i] = i;
        t = pthread_create(&thread[i], NULL, threadf, (void *)(&data[i]));
        if (t != 0)
            return 1;
    }
    for(int i = 0; i < threadc; i++)
    {
        t = pthread_join(thread[i], NULL);
        if(t != 0)
            // return 1;
    }  
    cout << "Modified 2-d Array: ";
    pArray(list, rows, cols);
    return 0;
}