// Задание 2. Многопоточная программа «Hello World!»

#include <omp.h>
#include <stdio.h>

int main() {
  // omp_set_num_threads(10);
#pragma omp parallel num_threads(3)
  { printf("Hello World!\n"); }

  return 0;
}