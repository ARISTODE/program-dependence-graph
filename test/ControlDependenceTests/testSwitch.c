#include<stdio.h>

int main() {
    int x = 2;

    switch(x) {
        case 1:
            printf("x equals 1\n");
            break;
        case 2:
            printf("x equals 2\n");
            break;
        default:
            printf("x is not 1 or 2\n");
    }

    return 0;
}
