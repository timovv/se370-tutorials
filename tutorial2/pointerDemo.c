#include <stdio.h>
#include <stdlib.h>

struct MyStruct {
    int a;
    int b;
};

void pointers(void) {
    int value = NULL;
    int *pointsToValue = &value;
    int *nullx = NULL;

    printf("pointsToValue is %d\n", pointsToValue);
    printf("value is %d\n", value);
    printf("dereferencing pointsToValue gives %d\n", *pointsToValue);
}

void structs(void) {
    struct MyStruct data;

    data.a = 4535;
    data.b = 4;

    struct MyStruct *dataPointer = &data;
    dataPointer->a = 4;
}

int result;

// What's wrong with this?
int* badPointer(void) {
    int* x = malloc(sizeof(int));
    *x = 3;
}

int main(const int argc, const char **argv) {

    // 2. What's the problem?
    // How would I fix this?
    int *result = badPointer();
    printf("Result is %d\n", *result);
    free(result);
}

