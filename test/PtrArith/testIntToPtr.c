#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int *ptr = arr;
    int*k = (int)ptr + 4;
    printf("%d\n", *k);
    return 0;
}
