#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Graph-Adjacency List Struct
typedef struct graph {
    int vertices;
    struct list_node** adj_list;
} graph; 

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
    node* temp = head; // This is a temporary variable that will be used to traverse the list
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next; 
    }
    printf("\n");
}

// Create Graph Function
graph* create_graph(int vertices) {
    graph* new_graph = (graph*)malloc(sizeof(graph));
    new_graph->vertices = vertices;
    new_graph->adj_list = (node**)malloc(vertices * sizeof(node*));
    for (int i = 0; i < vertices; i++) {
        new_graph->adj_list[i] = NULL;
    }
    return new_graph;
}

// Add Edge Function
void add_edge(graph* graph, int src, int dest) {
    node* new_node = create_list(dest);
    new_node->next = graph->adj_list[src];
    graph->adj_list[src] = new_node;
    new_node = create_list(src);
    new_node->next = graph->adj_list[dest];
    graph->adj_list[dest] = new_node;
}

// Print Graph Function
void print_graph(graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        node* temp = graph->adj_list[i];
        printf("Vertex %d: ", i);
        while (temp != NULL) {
            printf("%d ", temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Adjacency Matrix Graph Struct
typedef struct graph {
    int vertices;
    int** adj_matrix;
} graph;

// Create Graph Function
graph* create_graph(int vertices) {
    graph* new_graph = (graph*)malloc(sizeof(graph));
    new_graph->vertices = vertices;
    new_graph->adj_matrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        new_graph->adj_matrix[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            new_graph->adj_matrix[i][j] = 0;
        }
    }
    return new_graph;
}

// Add Edge Function
void add_edge(graph* graph, int src, int dest) {
    graph->adj_matrix[src][dest] = 1;
    graph->adj_matrix[dest][src] = 1;
}

// Print Graph Function
void print_graph(graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        printf("Vertex %d: ", i);
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->adj_matrix[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}

// Depth First Search Function
void dfs(graph* graph, int start, bool* visited) {
    visited[start] = true;
    printf("%d ", start);
    node* temp = graph->adj_list[start];
    while (temp != NULL) {
        int adj_vertex = temp->value;
        if (!visited[adj_vertex]) {
            dfs(graph, adj_vertex, visited);
        }
        temp = temp->next;
    }
}

// Breadth First Search Function
void bfs(graph* graph, int start, bool* visited) {
    node* queue = create_list(start);
    visited[start] = true;
    while (queue != NULL) {
        int vertex = queue->value;
        printf("%d ", vertex);
        node* temp = graph->adj_list[vertex];
        while (temp != NULL) {
            int adj_vertex = temp->value;
            if (!visited[adj_vertex]) {
                visited[adj_vertex] = true;
                queue = create_list(adj_vertex);
            }
            temp = temp->next;
        }
        queue = queue->next;
    }
}

// Stack Struct
typedef struct stack_node {
    int value;
    struct stack_node* next;
} stack;

// Create Stack Function
stack* create_stack() {
    return NULL;
}

// Push Function
void push(stack** head, int value) {
    stack* new_node = (stack*)malloc(sizeof(stack));
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}

// Pop Function
int pop(stack** head) {
    if (*head == NULL) {
        return -1;
    }
    stack* temp = *head;
    *head = (*head)->next;
    int value = temp->value;
    free(temp);
    return value;
}

// Queue Struct
typedef struct queue_node {
    int value;
    struct queue_node* next;
} queue;

// Create Queue Function
queue* create_queue() {
    return NULL;
}

// Enqueue Function
void enqueue(queue** head, int value) {
    queue* new_node = (queue*)malloc(sizeof(queue));
    new_node->value = value;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        queue* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Dequeue Function
int dequeue(queue** head) {
    if (*head == NULL) {
        return -1;
    }
    queue* temp = *head;
    *head = (*head)->next;
    int value = temp->value;
    free(temp);
    return value;
}

// Dikjstra's Algorithm Function
void dijkstra(graph* graph, int start) {
    int vertices = graph->vertices;
    int* distances = (int*)malloc(vertices * sizeof(int));
    bool* visited = (bool*)malloc(vertices * sizeof(bool));
    for (int i = 0; i < vertices; i++) {
        distances[i] = INT_MAX;
        visited[i] = false;
    }
    distances[start] = 0;
    for (int i = 0; i < vertices - 1; i++) {
        int min = INT_MAX;
        int min_index;
        for (int j = 0; j < vertices; j++) {
            if (!visited[j] && distances[j] <= min) {
                min = distances[j];
                min_index = j;
            }
        }
        visited[min_index] = true;
        node* temp = graph->adj_list[min_index];
        while (temp != NULL) {
            int adj_vertex = temp->value;
            int weight = temp->weight;
            if (!visited[adj_vertex] && distances[min_index] != INT_MAX && distances[min_index] + weight < distances[adj_vertex]) {
                distances[adj_vertex] = distances[min_index] + weight;
            }
            temp = temp->next;
        }
    }
    for (int i = 0; i < vertices; i++) {
        printf("%d ", distances[i]);
    }
}

// Prim's Algorithm Function
void prim(graph* graph) {
    int vertices = graph->vertices;
    int* parent = (int*)malloc(vertices * sizeof(int));
    int* key = (int*)malloc(vertices * sizeof(int));
    bool* visited = (bool*)malloc(vertices * sizeof(bool));
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        visited[i] = false;
    }
    key[0] = 0;
    parent[0] = -1;
    for (int i = 0; i < vertices - 1; i++) {
        int min = INT_MAX;
        int min_index;
        for (int j = 0; j < vertices; j++) {
            if (!visited[j] && key[j] < min) {
                min = key[j];
                min_index = j;
            }
        }
        visited[min_index] = true;
        node* temp = graph->adj_list[min_index];
        while (temp != NULL) {
            int adj_vertex = temp->value;
            int weight = temp->weight;
            if (!visited[adj_vertex] && weight < key[adj_vertex]) {
                parent[adj_vertex] = min_index;
                key[adj_vertex] = weight;
            }
            temp = temp->next;
        }
    }
    for (int i = 1; i < vertices; i++) {
        printf("%d - %d\n", parent[i], i);
    }
}