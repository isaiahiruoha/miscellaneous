#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Linked List Stack

typedef struct list_node { // This is a struct that will be used to create a linked list
    int value;
    struct list_node *next;
} node;

node* create_list(int data) {  // This function creates a list with a single element
    node* head = (node*)malloc(sizeof(node));
    head->next = NULL;
    head->value = data; 
    return head; 
}

void print_list(node* head) {
    node* temp = head; // This is a temporary variable that will be used to traverse the list
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next; 
    }
    printf("\n");
}

bool pop(node** head, int* value) { // This function removes the first element of the list and returns it
    if (*head == NULL) {
        return false; 
    }
    node* next_node = (*head)->next;
    *value = (*head)->value;
    free(*head);
    *head = next_node;
    return true;
}

bool push(node** head, int value) { // This function adds an element to the beginning of the list
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        return false; 
    }
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
    return true;
}

// Array List Stack

typedef struct array_list { // This is a struct that will be used to create an array list
    int *arr;
    int size;
    int capacity;
} array_list;

array_list* create_array_list(int capacity) { // This function creates an array list
    array_list* list = (array_list*)malloc(sizeof(array_list));
    list->arr = (int*)malloc(capacity * sizeof(int));
    list->size = 0;
    list->capacity = capacity;
    return list;
}

void print_array_list(array_list* list) { // This function prints the array list
    for (int i = 0; i < list->size; i++) {
        printf("%d", list->arr[i]);
        if (i != list->size - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

bool pop_array_list(array_list* list, int* value) { // This function removes the last element of the list and returns it
    if (list->size == 0) {
        return false;
    }
    *value = list->arr[list->size - 1];
    list->size--;
    return true;
}

bool push_array_list(array_list* list, int value) { // This function adds an element to the end of the list
    if (list->size == list->capacity) {
        return false;
    }
    list->arr[list->size] = value;
    list->size++;
    return true;
}

// Linked List Queue 

typedef struct queue_node { // This is a struct that will be used to create a queue
    int value;
    struct queue_node *next;
} queue_node;

bool enqueue(queue_node** head, queue_node** tail, int value) { // This function adds an element to the end of the queue
    queue_node* new_node = (queue_node*)malloc(sizeof(queue_node));
    if (new_node == NULL) {
        return false;
    }
    new_node->value = value;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        (*tail)->next = new_node;
    }
    *tail = new_node;
    return true;
}

bool dequeue(queue_node** head, queue_node** tail, int* value) { // This function removes the first element of the queue and returns it
    if (*head == NULL) {
        return false;
    }
    *value = (*head)->value;
    queue_node* temp = *head;
    *head = (*head)->next;
    free(temp);
    if (*head == NULL) {
        *tail = NULL;
    }
    return true;
}

void print_queue(queue_node* head) { // This function prints the queue
    queue_node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

// Array Circular Queue

typedef struct array_queue { // This is a struct that will be used to create a circular queue
    int *arr;
    int size;
    int capacity;
    int front;
    int rear;
} array_queue;

array_queue* create_array_queue(int capacity) { // This function creates a circular queue
    array_queue* queue = (array_queue*)malloc(sizeof(array_queue));
    queue->arr = (int*)malloc(capacity * sizeof(int));
    queue->size = 0;
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    return queue;
}

bool enqueue_array_queue(array_queue* queue, int value) { // This function adds an element to the end of the queue
    if (queue->size == queue->capacity) {
        return false;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = value;
    queue->size++;
    return true;
}

bool dequeue_array_queue(array_queue* queue, int* value) { // This function removes the first element of the queue and returns it
    if (queue->size == 0) {
        return false;
    }
    *value = queue->arr[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return true;
}

void print_array_queue(array_queue* queue) { // This function prints the queue
    for (int i = 0; i < queue->size; i++) {
        printf("%d", queue->arr[(queue->front + i) % queue->capacity]);
        if (i != queue->size - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

// Priority Queue

typedef struct priority_queue_node { // This is a struct that will be used to create a priority queue
    int value;
    int priority;
    struct priority_queue_node *next;
} priority_queue_node;

bool enqueue_priority_queue(priority_queue_node** head, int value, int priority) { // This function adds an element to the queue based on its priority
    priority_queue_node* new_node = (priority_queue_node*)malloc(sizeof(priority_queue_node));
    if (new_node == NULL) {
        return false;
    }
    new_node->value = value;
    new_node->priority = priority;
    if (*head == NULL || (*head)->priority > priority) {
        new_node->next = *head;
        *head = new_node;
    } else {
        priority_queue_node* temp = *head;
        while (temp->next != NULL && temp->next->priority <= priority) {
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
    return true;
}

bool dequeue_priority_queue(priority_queue_node** head, int* value) { // This function removes the first element of the queue and returns it
    if (*head == NULL) {
        return false;
    }
    *value = (*head)->value;
    priority_queue_node* temp = *head;
    *head = (*head)->next;
    free(temp);
    return true;
}

void print_priority_queue(priority_queue_node* head) { // This function prints the queue
    priority_queue_node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

