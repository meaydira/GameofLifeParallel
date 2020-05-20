#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#ifdef _OPENMP
int my_rank = omp_get_thread_num();
int thread_count = omp_get_num_threads();
#else
int my_rank = 0;
int thread_count = 1;
#end

int omp_get_thread_num();
int omp_get_num_threads();


int main (int argc, char* argv[])
{

  int thread_count= 5;

#pragma omp parallel num_threads(thread_count)
    {
      int myID = omp_get_thread_num();

      int num_threads = omp_get_num_threads();
      printf("Hello from thread %d of %d\n", myID, num_threads);
    }

  return 0;
}
