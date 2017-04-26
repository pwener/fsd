#include <mpi.h>
#include <stdio.h>
#include <math.h>

#define VECTOR_LEN 1000000000

int main(int argc, char** argv) {
  // Initialize the MPI environment. The two arguments to MPI Init are not
  // currently used by MPI implementations, but are there in case future
  // implementations might need the arguments.
  MPI_Init(NULL, NULL);

  // Get the number of processes
  int world_size = 1;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  float v[VECTOR_LEN];

  int x;

  for(x = 0; x < VECTOR_LEN; x++) {
    v[x] = pow((x - (VECTOR_LEN/2)), 2);
  }

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
