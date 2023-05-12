// Задание 18. Коммуникации «точка-точка»: схема «эстафетная палочка»

#include <mpi.h>
#include <stdio.h>

static const int kTag = 1337;

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (size < 2) {
    MPI_Finalize();
    return -1;
  }

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    int start_value = 0;
    MPI_Send(&start_value, 1, MPI_INT, rank + 1, kTag, MPI_COMM_WORLD);

    int recv_value;
    MPI_Status status;
    MPI_Recv(&recv_value, 1, MPI_INT, size - 1, kTag, MPI_COMM_WORLD, &status);

    if (status.MPI_ERROR == MPI_SUCCESS)
      printf("[%d]: receive message \'%d\'\n", rank, recv_value);
  } else {
    int recv_value;
    MPI_Status status;
    MPI_Recv(&recv_value, 1, MPI_INT, rank - 1, kTag, MPI_COMM_WORLD, &status);

    if (status.MPI_ERROR == MPI_SUCCESS)
      printf("[%d]: receive message \'%d\'\n", rank, recv_value);

    ++recv_value;
    MPI_Send(&recv_value, 1, MPI_INT, rank + 1 == size ? 0 : rank + 1, kTag,
             MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}