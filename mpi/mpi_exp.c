#include <mpi.h>
#include <stdio.h>
#include <math.h>

#define VECTOR_LEN 1000

#define MAIN_TASK_ID 0
#define FIRST_NOMAIN_TASK_ID 1

#define TAG1 7
#define TAG2 14

/**
 * Alocate vector space, at this point the MPI manages
 * that area with especial spaces.
 */
int fill_vector(float v[VECTOR_LEN]) {
	int index;
	for(index = 1; index < VECTOR_LEN; index++) {
		v[index] = pow((index - (VECTOR_LEN/2)), 2);
	}
}

void assign_chunks(float *v, int chunk_size, int task_numbers) {
	// Attribute chunks of work to each tasks
	int offset = chunk_size;

	int assigned_task_id;
	for(assigned_task_id = FIRST_NOMAIN_TASK_ID; assigned_task_id < task_numbers; assigned_task_id++) {
		if(offset < VECTOR_LEN) {
			MPI_Send(&v[offset], chunk_size, MPI_FLOAT, assigned_task_id, TAG2, MPI_COMM_WORLD);
			offset = offset + chunk_size;
			printf("Sent %d elements to task %d\n", chunk_size, assigned_task_id);
		} else {
			printf("Invalid offset, bigger than array size");
		}
	}
}

void block_and_receive(float *v, int chunk_size, int task_numbers) {
	// Needed for MPI_Recv bellow
	MPI_Status status;

	// reuse variable
	int offset = chunk_size;

	// Waits each task to receive result
	int source_task_id;
	for(source_task_id = FIRST_NOMAIN_TASK_ID; source_task_id < task_numbers; source_task_id++) {
		MPI_Recv(&v[offset], chunk_size, MPI_FLOAT, source_task_id, TAG2, MPI_COMM_WORLD, &status);
		offset = offset + chunk_size;
	}
}

float get_bigger(float *v, int offset, int chunk_size) {
		float bigger = 0;

		int index;
		for(index = offset; index < offset+chunk_size; index++) {
			v[index] = sqrt(v[index]);
			if(v[index] > bigger) {
				bigger = v[index];
			} else {
				// do nothing...
			}
		}

		return bigger;
}

float get_smaller(float *v, int offset, int chunk_size) {
	float smaller = 0;

	int index;
	for(index = offset; index < offset+chunk_size; index++) {
		v[index] = sqrt(v[index]);
		if(v[index] < smaller) {
			smaller = v[index];
		} else {
			// do nothing...
		}
	}

	return smaller;
}

int main(int argc, char* argv[]) {
	// declare vector
	float v[VECTOR_LEN];

	MPI_Init(&argc, &argv);

	// Get the number of processes
	int task_numbers;
	MPI_Comm_size(MPI_COMM_WORLD, &task_numbers);

	// Needed for MPI_Recv bellow
	MPI_Status status;

	/** Commom variables **/
	float task_bigger_value, real_bigger_value;
	float task_smaller_value, real_smaller_value;
	int task_id;
	// Lenght of chunk of work
	int chunk_size = VECTOR_LEN / task_numbers;

	// Working with paralel programming, each task would filled into task_id
	MPI_Comm_rank(MPI_COMM_WORLD, &task_id);

	printf("Runs task %d\n", task_id);

	// Main task
	if (task_id == MAIN_TASK_ID) {
		printf("Into main task\n");

		fill_vector(v);

		assign_chunks(v, chunk_size, task_numbers);

		block_and_receive(v, chunk_size, task_numbers);

		MPI_Reduce(&task_bigger_value, &real_bigger_value, 1, MPI_INT, MPI_MAX, MAIN_TASK_ID, MPI_COMM_WORLD);
		MPI_Reduce(&task_smaller_value, &real_smaller_value, 1, MPI_INT, MPI_MIN, MAIN_TASK_ID, MPI_COMM_WORLD);

		printf("The bigger found is %f\n", task_bigger_value);
		printf("The smaller found is %f\n", task_smaller_value);
	} else if (task_id > MAIN_TASK_ID) {
		// offset of task
		int offset = task_id * chunk_size;

		// Non main tasks
		MPI_Recv(&v[offset], chunk_size, MPI_FLOAT, MAIN_TASK_ID, TAG2, MPI_COMM_WORLD, &status);

		task_bigger_value = get_bigger(v, offset, chunk_size);
		task_smaller_value = get_smaller(v, offset, chunk_size);

		printf("Bigger found in %d is %e\n", task_id, task_bigger_value);
		printf("Smaller found in %d is %e\n", task_id, task_smaller_value);

		MPI_Send(&v[offset], chunk_size, MPI_FLOAT, MAIN_TASK_ID, TAG2, MPI_COMM_WORLD);

		MPI_Reduce(&task_bigger_value, &real_bigger_value, 1, MPI_INT, MPI_MAX, MAIN_TASK_ID, MPI_COMM_WORLD);
		MPI_Reduce(&task_smaller_value, &real_smaller_value, 1, MPI_INT, MPI_MIN, MAIN_TASK_ID, MPI_COMM_WORLD);
	} else {
		// invalid condition, finish program
		printf("Error when run tasks\n");
		MPI_Finalize();
		return;
	}

	// Finalize the MPI environment. No more MPI calls can be made after this
	MPI_Finalize();
}
