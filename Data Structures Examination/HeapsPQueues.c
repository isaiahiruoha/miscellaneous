#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Min Heap Struct
typedef struct min_heap {
    int *arr;
    int size;
    int capacity;
} min_heap;

// Create Min Heap Function
min_heap* create_min_heap(int capacity) {
    min_heap* heap = (min_heap*)malloc(sizeof(min_heap));
    heap->arr = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Insert Function
void insert(min_heap* heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap is full.\n");
        return;
    }
    heap->size++;
    int index = heap->size - 1;
    heap->arr[index] = value;
    while (index != 0 && heap->arr[(index - 1) / 2] > heap->arr[index]) {
        int temp = heap->arr[index];
        heap->arr[index] = heap->arr[(index - 1) / 2];
        heap->arr[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

// Print Function
void print(min_heap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d", heap->arr[i]);
        if (i != heap->size - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

// Remove Function
void remove_min(min_heap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty.\n");
        return;
    }
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    int index = 0;
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        if (left < heap->size && heap->arr[left] < heap->arr[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->arr[right] < heap->arr[smallest]) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        int temp = heap->arr[index];
        heap->arr[index] = heap->arr[smallest];
        heap->arr[smallest] = temp;
        index = smallest;
    }
}

// Max Heap Struct
typedef struct max_heap {
    int *arr;
    int size;
    int capacity;
} max_heap;

// Create Max Heap Function
max_heap* create_max_heap(int capacity) {
    max_heap* heap = (max_heap*)malloc(sizeof(max_heap));
    heap->arr = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Insert Function
void insert(max_heap* heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap is full.\n");
        return;
    }
    heap->size++;
    int index = heap->size - 1;
    heap->arr[index] = value;
    while (index != 0 && heap->arr[(index - 1) / 2] < heap->arr[index]) {
        int temp = heap->arr[index];
        heap->arr[index] = heap->arr[(index - 1) / 2];
        heap->arr[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

// Print Function
void print(max_heap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d", heap->arr[i]);
        if (i != heap->size - 1) {
            printf(", ");
        }
    }
    printf("\n");
}