       
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "timer.h"

const int MAX_THREADS = 1024;

int thread_count;
int m;
int n;
int k;
int computed_elements;
float* matrix;
pthread_mutex_t mutex;
pthread_cond_t condition_variable;

void* Thread_computation(void* rank);

/* Only executed by main thread */
void Get_args(int argc, char* argv[]);

int main(int argc, char* argv[]) {
   long       thread;  /* Use long in case of a 64-bit system */
   pthread_t* thread_handles;
   double start, finish, elapsed;

   /* Get number of threads, rows and columns from command line */
   Get_args(argc, argv);

   /* Create the matrix */
   matrix = (float *)malloc(m * n * sizeof(float)); 

   thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t)); 
   pthread_mutex_init(&mutex, NULL);
   pthread_cond_init (&condition_variable, NULL);
   srand(time(NULL));

   /* Initialize the matrix */
   int upper = 9;
   int lower = 1;
   for(int i = 0; i < m; i++) {
   		for(int j = 0; j < n; j++) {
   			if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
   				*(matrix + i * n + j) = (rand() % (upper - lower + 1)) + lower;
   			} else {
   				*(matrix + i * n + j) = 0;
   			} 
   		}
   }

   /* Print the initial matrix */
   //printf("Initial matrix\n");
   for(int i = 0; i < m; i++) {
      for(int j = 0; j < n; j++) {
        //printf("%f     ", *(matrix + i * n + j));
      }
      //printf("\n");
   }

   //printf("\n");
   GET_TIME(start);
   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL, Thread_computation, (void*)thread);  

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 
   GET_TIME(finish);
   elapsed = finish - start;

   //printf("\n");
   /* Print the final matrix */
   for(int i = 0; i < m; i++) {
   		for(int j = 0; j < n; j++) {
   			//printf("%f     ", *(matrix + i * n + j));
   		}
   		//printf("\n");
   }

   printf("\n");
   printf("The elapsed time is %e seconds\n", elapsed);
   //printf("Computed elements: %d\n", computed_elements);
   printf("\n");

   pthread_mutex_destroy(&mutex);
   pthread_cond_destroy(&condition_variable);
   free(thread_handles);
   free(matrix);
   return 0;
}  /* main */

/*------------------------------------------------------------------*/
void* Thread_computation(void* rank) {
   	int my_rank = (int) rank;
    //printf("Thread %d started.\n", my_rank);

  	/* Interval on which each thread will operate */
  	float number_of_columns = (n - 2) / 350.0;
  	float number_of_threads = thread_count / 350.0;
  	int columns_per_thread = ceil(number_of_columns / number_of_threads);
  	
    for(int iteration = 0; iteration < k; iteration++) {
      for(int i = 1; i < m - 1; i++) {
      	for(int j = 1; j <= columns_per_thread; j++) {
      		int assigned_column = my_rank * columns_per_thread + j;
      		if (assigned_column != n - 1) {
            pthread_mutex_lock(&mutex);
            while (*(matrix + i * n + (assigned_column - 1)) == 0) {
              /* Wait until element from left is computed */
              //printf("Thread %d is waiting...\n", my_rank);
              pthread_cond_wait(&condition_variable, &mutex);
            }

            /* Modifying the matrix */
            if (*(matrix + i * n + (assigned_column - 1)) != 0) {
              *(matrix + i * n + assigned_column) = (*(matrix + (i - 1) * n + assigned_column) + *(matrix + (i + 1) * n + assigned_column) + *(matrix + i * n + (assigned_column - 1)) + *(matrix + i * n + (assigned_column + 1))) / 4;
      		    //printf("Compute element M[%d,%d]\n", i, assigned_column);
              computed_elements++;
              pthread_cond_signal(&condition_variable);
              pthread_mutex_unlock(&mutex);
            }
          }
      	}
      }
    }
   
   	return NULL;
}  /* Thread_computation */

/*------------------------------------------------------------------
 * Function:    Get_args
 * Purpose:     Get the command line args
 * In args:     argc, argv
 * Globals out: thread_count, m, n
 */
void Get_args(int argc, char* argv[]) {
   thread_count = atoi(argv[1]);  
   m = atoi(argv[2]);
   n = atoi(argv[3]);
   k = atoi(argv[4]);
}  /* Get_args */

