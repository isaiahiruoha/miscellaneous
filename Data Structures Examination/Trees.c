#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Basic Binary Tree is a tree with at most 2 children

// Binary Tree Struct
typedef struct binary_tree_node {
    int value;
    struct binary_tree_node *left;
    struct binary_tree_node *right;
} node;

// Create Binary Tree Function
node* create_binary_tree(int value) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Insert Function
void insert(node* root, int value) {
    if (value < root->value) {
        if (root->left == NULL) {
            root->left = create_binary_tree(value);
        } else {
            insert(root->left, value);
        }
    } else {
        if (root->right == NULL) {
            root->right = create_binary_tree(value);
        } else {
            insert(root->right, value);
        }
    }
}

// Print Function
void print(node* root) { // This function prints the values of the tree in order traversal
    if (root == NULL) {
        return;
    }
    print(root->left);
    printf("%d ", root->value);
    print(root->right);
}

// Search Function
bool search(node* root, int value) {
    if (root == NULL) {
        return false;
    }
    if (root->value == value) {
        return true;
    }
    if (value < root->value) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

// Delete Function
void delete(node* root, int value) {
    if (root == NULL) {
        return;
    }
    if (value < root->value) {
        delete(root->left, value);
    } else if (value > root->value) {
        delete(root->right, value);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        } else if (root->left == NULL) {
            node* temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL) {
            node* temp = root;
            root = root->left;
            free(temp);
        } else {
            node* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->value = temp->value;
            delete(root->right, temp->value);
        }
    }
}

// Level Order Traversal 
// void level_order_traversal(node* root) {
//     if (root == NULL) {
//         return;
//     }
//     queue* queue = create_queue();
//     enqueue(queue, root);
//     while (queue->size != 0) {
//         node* temp = NULL;
//         dequeue(queue, &temp);
//         printf("%d ", temp->value);
//         if (temp->left != NULL) {
//             enqueue(queue, temp->left);
//         }
//         if (temp->right != NULL) {
//             enqueue(queue, temp->right);
//         }
//     }
// }

// Binarary Search Tree

// Create Binary Search Tree Function
node* create_binary_search_tree(int value) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Insert Function
void insert(node* root, int value) {
    if (value < root->value) {
        if (root->left == NULL) {
            root->left = create_binary_search_tree(value);
        } else {
            insert(root->left, value);
        }
    } else {
        if (root->right == NULL) {
            root->right = create_binary_search_tree(value);
        } else {
            insert(root->right, value);
        }
    }
}

// Print Function
void print(node* root) { // This function prints the values of the tree in order traversal
    if (root == NULL) {
        return;
    }
    print(root->left);
    printf("%d ", root->value);
    print(root->right);
}

// Search Function
bool search(node* root, int value) {
    if (root == NULL) {
        return false;
    }
    if (root->value == value) {
        return true;
    }
    if (value < root->value) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

// Insert Function
void insert(node* root, int value) {
    if (value < root->value) {
        if (root->left == NULL) {
            root->left = create_binary_search_tree(value);
        } else {
            insert(root->left, value);
        }
    } else {
        if (root->right == NULL) {
            root->right = create_binary_search_tree(value);
        } else {
            insert(root->right, value);
        }
    }
}

// Delete Function
void delete(node* root, int value) {
    if (root == NULL) {
        return;
    }
    if (value < root->value) {
        delete(root->left, value);
    } else if (value > root->value) {
        delete(root->right, value);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        } else if (root->left == NULL) {
            node* temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL) {
            node* temp = root;
            root = root->left;
            free(temp);
        } else {
            node* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->value = temp->value;
            delete(root->right, temp->value);
        }
    }
}

// AVL Tree

// AVL Tree Struct
typedef struct avl_tree_node {
    int value;
    int height;
    struct avl_tree_node *left;
    struct avl_tree_node *right;
} node;

// Create AVL Tree Function
node* create_avl_tree(int value) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->value = value;
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


// Max Function
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Height Function
int height(node* root) {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

// Balance Factor Function
int balance_factor(node* root) {
    if (root == NULL) {
        return 0;
    }
    return height(root->left) - height(root->right);
}

// Right Rotate Function
node* right_rotate(node* root) {
    node* new_root = root->left;
    node* temp = new_root->right;
    new_root->right = root;
    root->left = temp;
    root->height = 1 + max(height(root->left), height(root->right));
    new_root->height = 1 + max(height(new_root->left), height(new_root->right));
    return new_root;
}

// Left Rotate Function
node* left_rotate(node* root) {
    node* new_root = root->right;
    node* temp = new_root->left;
    new_root->left = root;
    root->right = temp;
    root->height = 1 + max(height(root->left), height(root->right));
    new_root->height = 1 + max(height(new_root->left), height(new_root->right));
    return new_root;
}

// Insert Function
node* insert(node* root, int value) {
    if (root == NULL) {
        return create_avl_tree(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = balance_factor(root);
    if (balance > 1 && value < root->left->value) {
        return right_rotate(root);
    }
    if (balance < -1 && value > root->right->value) {
        return left_rotate(root);
    }
    if (balance > 1 && value > root->left->value) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (balance < -1 && value < root->right->value) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}

// Print Function
void print(node* root) { // This function prints the values of the tree in order traversal
    if (root == NULL) {
        return;
    }
    print(root->left);
    printf("%d ", root->value);
    print(root->right);
}
