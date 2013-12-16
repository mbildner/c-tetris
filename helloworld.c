#include <stdio.h>
#include <stdlib.h>

int qsort_comparator (const void* a, const void* b) {
	const int *int_a = a;
	const int *int_b = b;

	return *int_a - *int_b;

}

int main (int argc, char *argv[]) {

	int array_length = argc-1;

	int *num_array = malloc(sizeof(int) * (array_length));

	for (int i=1; i<argc; i++) {
		num_array[i-1] = atoi(argv[i]);
	}

	qsort (num_array, array_length, sizeof(int), qsort_comparator);

	for (int i=0; i<array_length; i++) {
		printf("%d\n", num_array[i]);
	}

	return 0;
}




