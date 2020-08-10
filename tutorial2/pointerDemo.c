#include <stdio.h>

struct MyStruct {
    int a;
    int b;
};

void pointers(void) {
    int value = 3;
    int *pointsToValue = &value;

    printf("pointsToValue is %d\n", pointsToValue);
    printf("value is %d\n", value);
    printf("dereferencing pointsToValue gives %d\n", *pointsToValue);
}

void structs(void) {
    struct MyStruct data;

    data.a = 3;
    data.b = 4;

    struct MyStruct *dataPointer = &data;
    printf("a=%d b=%d\n", dataPointer->a, dataPointer->b);
}

// What's wrong with this?
int* badPointer(void) {
    int b = 3;
    return &b;
}

int main(const int argc, const char **argv) {

    // 1. How do these values work?
    pointers();

    // 2. What's the problem?
    // How would I fix this?
    int *result = badPointer();

    // 3. Looking at structs
    structs();

    printf("Result is %d\n", *result);
}

