// Задание 15. Программа «I am!»

#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  printf("I am %d process from %d processes!\n", rank, size);

  MPI_Finalize();
  return 0;
}