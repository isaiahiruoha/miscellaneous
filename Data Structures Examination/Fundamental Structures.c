#include <stdio.h>

// Basic array example
void arrayExample() {
    int arr[5] = {1, 2, 3, 4, 5};
    printf("First element: %d\n", arr[0]);
    printf("Second element: %d\n", arr[1]);
    printf("Third element: %d\n", arr[2]);
    printf("Fourth element: %d\n", arr[3]);
    printf("Fifth element: %d\n", arr[4]);
}

// Dynamic array example without user input 
void dynamicArrayExample() {
    int *arr;
    int size = 5;
    arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    for (int i = 0; i < size; i++) {
        printf("Element %d: %d\n", i, arr[i]);
    }
}

// Dynamic Memory Management Examples
void dynamicMemoryManagementExample() {
    int *ptr_one;
    ptr_one = (int *)malloc(sizeof(int)); // This allocates memory for an integer
    *ptr_one = 25;
    printf("%d\n", *ptr_one);
    free(ptr_one);
    printf("%d\n", *ptr_one);
    // Additionally, calloc and realloc can be used to allocate memory shown below
    // calloc allocates memory and sets it to 0 given a pointer and a size
    // realloc reallocates memory given a pointer and a size
}

