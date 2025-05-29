#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    int age;
    char name[10];
};

void f(struct Person* p)
{
    printf("age of p is %d\n", p->age);
}

int main() {
    struct Person *p = (struct Person*)malloc(sizeof(struct Person));
    p->age = 5;
    strcpy(p->name, "Student");
    void (*fun_ptr)(struct Person*) = f;  // & removed
    fun_ptr(p);
    free(p);
    return 0;
}
