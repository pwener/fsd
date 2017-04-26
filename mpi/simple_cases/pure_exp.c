#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define VECTOR_LEN 1000000000

// V[i] = (i – tamanho_do_vetor/2) ** 2;
int main() {
	float v[VECTOR_LEN];

	int x;

	for(x = 0; x < VECTOR_LEN; x++) {
		v[x] = pow((x - (VECTOR_LEN/2)), 2);
	}

	return 0;
}
