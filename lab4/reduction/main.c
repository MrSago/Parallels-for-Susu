// Задание 5. Общие и частные переменные в OpenMP: параметр reduction

#include <math.h>
#include <omp.h>
#include <stdio.h>

int main() {
  int k, N;
  scanf("%d%d", &k, &N);
  if (k > N) k = N;

  int sum = 0;
  int count_iterations = (int)ceil((double)N / (double)k);

  int thread, start, end, i;

#pragma omp parallel num_threads(k) \
    reduction(+ : sum) private(thread, start, end, i)
  {
    thread = omp_get_thread_num();
    start = count_iterations * thread + 1;
    end = count_iterations * (thread + 1) + 1;

    for (i = start; i < end; ++i) sum += i;

    printf("[%d] : Sum = %d\n", thread, sum);
  }

  printf("Sum = %d\n", sum);

  return 0;
}