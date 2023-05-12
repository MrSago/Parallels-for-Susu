// Задание 17. Коммуникации «точка-точка»: простые блокирующие обмены

#include <mpi.h>
#include <stdio.h>

static const int kTag = 1337;

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (size != 2) {
    MPI_Finalize();
    return -1;
  }

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    int send_value = 35;
    MPI_Send(&send_value, 1, MPI_INT, 1, kTag, MPI_COMM_WORLD);
  } else {
    int recv_value;
    MPI_Status status;
    MPI_Recv(&recv_value, 1, MPI_INT, 0, kTag, MPI_COMM_WORLD, &status);

    if (status.MPI_ERROR == MPI_SUCCESS)
      printf("receive message \'%d\'", recv_value);
  }

  MPI_Finalize();
  return 0;
}