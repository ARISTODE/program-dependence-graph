#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void dereference_ptr(struct data* input) {
  int x = *(input->ptr); // Dereference ptr  
}

void controlled_malloc(struct data* input) {
  int* ptr = malloc(input->size); // Controlled malloc size
}

void free_ptr(struct data* input) {
  free(input->ptr); // Free pointer
}

void pointer_arithmetic(struct data* input) {
  int* ptr = input->ptr;
  ptr++; // Pointer arithmetic
}

void fSize(int* size) {
  free(size);
}

void sensitive_branch(struct data* input) { 
	int *alias = input->ptr;
	if (input->size > 10) {    
		//free(alias); // Sensitive op in branch
		int local_arr[10];
		printf("%d\n", local_arr[5]);
	}
	fSize(&input->size);
}

void array_indexing(int arr[10], struct data* input) {
	int x = arr[input->size]; // Array indexing
	int *local_arr = arr;
	int c = local_arr[5];
}
