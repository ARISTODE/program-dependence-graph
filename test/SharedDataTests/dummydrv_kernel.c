#include "header.h"
#include <stdlib.h>

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

void sensitive_branch(struct data* input) {
  if (input->size > 10) {    
    free(input->ptr); // Sensitive op in branch
  }
}

void array_indexing(int arr[10], struct data* input) {
  int x = arr[input->size]; // Array indexing
}
