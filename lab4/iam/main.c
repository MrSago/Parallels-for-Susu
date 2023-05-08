// Задание 3. Программа «I am!»

#include <omp.h>
#include <stdio.h>

int main() {
  int k;
  scanf("%d", &k);

  int num_thread, count_threads;

#pragma omp parallel num_threads(k) private(num_thread)
  {
    num_thread = omp_get_thread_num();
    count_threads = omp_get_num_threads();
    if (num_thread % 2 == 0)
      printf("I am %d thread from %d threads!\n", num_thread, count_threads);
  }

  return 0;
}