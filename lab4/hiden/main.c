// Задание 4. Общие и частные переменные в OpenMP: программа «Скрытая ошибка» 

#include <Windows.h>
#include <omp.h>
#include <stdio.h>

int main() {
  int k;
  scanf("%d", &k);

  int rank;
#pragma omp parallel num_threads(k) private(rank)
  {
    rank = omp_get_thread_num();
    Sleep(100);
    printf("I am %d thread.\n", rank);
  }

  return 0;
}