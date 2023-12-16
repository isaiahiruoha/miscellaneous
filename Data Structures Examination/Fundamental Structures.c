#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Linked List Struct
typedef struct list_node {
    int value;
    struct list_node *next;
} node;

// Create List Function
node* create_list(int data) { 
    node* head = (node*)malloc(sizeof(node));
    head->next = NULL;
    head->value = data; 
    return head; 
}

// Print List Function
void print_list(node* head) {
    node *temp = head; // This is a temporary variable that will be used to traverse the list or else the head will be lost
    while (temp != NULL) {
        printf("%d", temp->value); 
        temp = temp->next; 
        if (temp != NULL) {
           printf(", ");  
        }
    }
    printf("\n");
}

// Insert Last Function
void insert_at_tail(node** head, int data) { // This is a double pointer because we want to change the head pointer

// Imagine you have a house and you give a friend the key to your front door (analogous to a single pointer).
// If your friend copies the key and opens the door (modifies the copy), your original key is unchanged.
// Now, imagine you give your friend a special key that opens a box containing the key to your front door (analogous to a double pointer).
// If your friend changes the key in the box (modifies the content of the memory address the double pointer points to), your original key (the key to the front door) is also changed.

    node* new_node = (node*)malloc(sizeof(node)); 
    new_node->next = NULL;
    new_node->value = data; 
    if (*head == NULL) {
        *head = new_node; 
        return; 
    }
    node* temp = *head; 
    while (temp->next != NULL) { 
        temp = temp->next; 
    }
    temp->next = new_node; 
}

// Swap Adjacent Function
void swap_adjacent(node* head) {
    node* temp = head; // This is a temporary variable that will be used to traverse the list
    while(temp != NULL && temp->next != NULL)
    {
        int temp_val = temp->value;
        temp->value = temp->next->value;
        temp->next->value = temp_val;
        temp = temp->next->next;
    }
}

// Double List Function
void double_list(node* head) {
    if (head == NULL) {
        return; 
    }

    node* tail = head; // This is a temporary variable that will be used to traverse the list

    while (tail->next != NULL) {
        tail = tail->next; 
    } // This while loop finds the tail of the list

    node* newHead = NULL;
    node* newCurrent = NULL;

    while (head != NULL) {
        node *newNode = (node*)malloc(sizeof(node));
            newNode->value = head->value;
            newNode->next = NULL;

            if (newHead == NULL) {
                newHead = newNode;
                newCurrent = newNode;
            } else {
                newCurrent->next = newNode;
                newCurrent = newNode;
            }
        head = head->next;
    }
    tail->next = newHead;
}

// Remove Adjacent Duplicates Function
void remove_adjacent_duplicates(node* head) {
    node* temp = head;
    while(temp != NULL && temp->next != NULL)
    {
        if(temp->value == temp->next->value)
        {
            node* node_to_delete = temp->next;
            temp->next = temp->next->next;
            free(node_to_delete); 
        }
        else
        {
            temp = temp->next;
        }
    }
}

// Remove First
void remove_first(node** head) {
    if (*head == NULL) {
        return; 
    }
    node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Search Function
bool search(node* head, int data) {
    node* temp = head;
    while(temp != NULL)
    {
        if(temp->value == data)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Delete Function
void delete(node** head, int data) {
    if (*head == NULL) {
        return; 
    }
    node* temp = *head;
    if (temp->value == data) {
        *head = (*head)->next;
        free(temp);
        return;
    }
    while(temp->next != NULL)
    {
        if(temp->next->value == data)
        {
            node* node_to_delete = temp->next;
            temp->next = temp->next->next;
            free(node_to_delete);
            return;
        }
        temp = temp->next;
    }
}

// To implement a doubly linked list the following must change
// The struct must have a previous pointer
// The create_list function must set the previous pointer to NULL
// The insert_at_tail function must set the previous pointer to the previous node
// The print_list function must print the previous node
// The swap_adjacent function must swap the previous node
// The double_list function must double the previous node
// The remove_adjacent_duplicates function must remove the previous node
// The remove_first function must remove the previous node
// The search function must search the previous node

// Array list struct
typedef struct array_list {
    int *arr;
    int size;
    int capacity;
} array_list;

// Create array list function
array_list* create_array_list(int capacity) {
    array_list* list = (array_list*)malloc(sizeof(array_list));
    list->arr = (int*)malloc(capacity * sizeof(int));
    list->size = 0;
    list->capacity = capacity;
    return list;
}

// Print array list function
void print_array_list(array_list* list) {
    for (int i = 0; i < list->size; i++) {
        printf("%d", list->arr[i]);
        if (i != list->size - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

// Insert at tail function
void insert_at_tail_array_list(array_list* list, int data) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->arr = (int*)realloc(list->arr, list->capacity * sizeof(int));
    }
    list->arr[list->size] = data;
    list->size++;
}

// Remove element function
void remove_element(array_list* list, int index) {
    if (index < 0 || index >= list->size) {
        return;
    }
    for (int i = index; i < list->size - 1; i++) {
        list->arr[i] = list->arr[i + 1];
    }
    list->size--;
}