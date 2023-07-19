#include "header.h"


int main() {

  struct data myData;
  int x = 10;
  myData.ptr = &x;
  dereference_ptr(&myData);

  myData.size = 100;
  controlled_malloc(&myData);
   
  int y = 20; 
  myData.ptr = &y; 
  free_ptr(&myData);

  myData.ptr = &x;
  pointer_arithmetic(&myData);

  myData.size = 15;
  sensitive_branch(&myData);

  int array[10];
  myData.size = 5;
  array_indexing(array, &myData);

  return 0;
}
