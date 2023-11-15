#include <stdio.h>
#include <stdlib.h>

// Define a structure for a BST node
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Define a structure for a stack node
struct StackNode {
    struct TreeNode *node;
    struct StackNode *next;
};

// Function prototypes
struct TreeNode* createBST(struct TreeNode* root, int key);
struct TreeNode* deleteNode(struct TreeNode* root, int key);
void inOrderTraversal(struct TreeNode* root);
void freeTree(struct TreeNode* root);
void push(struct StackNode** top, struct TreeNode* node);
struct TreeNode* pop(struct StackNode** top);

// Function to create a BST (Iterative)
struct TreeNode* createBST(struct TreeNode* root, int key) {
    if (root == NULL) {
        struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newNode->data = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    struct TreeNode* current = root;
    struct TreeNode* parent = NULL;

    while (current != NULL) {
        parent = current;

        if (key < current->data) {
            current = current->left;
        } else if (key > current->data) {
            current = current->right;
        } else {
            // Duplicate keys are not allowed
            return root;
        }
    }

    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = key;
    newNode->left = newNode->right = NULL;

    if (key < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}

// Function to delete a node from the BST (Iterative)
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    struct TreeNode* current = root;
    struct TreeNode* parent = NULL;

    while (current != NULL) {
        if (key < current->data) {
            parent = current;
            current = current->left;
        } else if (key > current->data) {
            parent = current;
            current = current->right;
        } else {
            // Node with only one child or no child
            if (current->left == NULL) {
                struct TreeNode* temp = current->right;
                if (parent == NULL) {
                    root = temp;
                } else if (current == parent->left) {
                    parent->left = temp;
                } else {
                    parent->right = temp;
                }
                free(current);
                return root;
            } else if (current->right == NULL) {
                struct TreeNode* temp = current->left;
                if (parent == NULL) {
                    root = temp;
                } else if (current == parent->left) {
                    parent->left = temp;
                } else {
                    parent->right = temp;
                }
                free(current);
                return root;
            }

            // Node with two children, replace with the in-order successor
            struct TreeNode* successorParent = current;
            struct TreeNode* successor = current->right;

            while (successor->left != NULL) {
                successorParent = successor;
                successor = successor->left;
            }

            current->data = successor->data;

            if (successorParent == current) {
                successorParent->right = successor->right;
            } else {
                successorParent->left = successor->right;
            }

            free(successor);
            return root;
        }
    }

    return root;
}

// Function to perform in-order traversal of the BST (Iterative)
void inOrderTraversal(struct TreeNode* root) {
    struct StackNode* stack = NULL;
    struct TreeNode* current = root;

    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }

        current = pop(&stack);
        printf("%d ", current->data);

        current = current->right;
    }

    printf("\n");
}

// Function to push a node onto the stack
void push(struct StackNode** top, struct TreeNode* node) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->node = node;
    newNode->next = *top;
    *top = newNode;
}

// Function to pop a node from the stack
struct TreeNode* pop(struct StackNode** top) {
    if (*top == NULL) {
        return NULL;
    }

    struct StackNode* temp = *top;
    struct TreeNode* node = temp->node;
    *top = temp->next;
    free(temp);
    return node;
}

// Function to free the memory allocated for the tree
void freeTree(struct TreeNode* root) {
    struct StackNode* stack = NULL;
    struct TreeNode* current = root;

    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            if (current->right != NULL) {
                push(&stack, current->right);
            }
            struct TreeNode* temp = current;
            current = current->left;
            free(temp);
        }

        current = pop(&stack);
    }
}

// Main function
int main() {
    struct TreeNode* root = NULL;
    int choice, key;

    do {
        printf("\nMenu:\n");
        printf("1. Insert element\n");
        printf("2. Delete element\n");
        printf("3. Display elements (In-order traversal)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &key);
                root = createBST(root, key);
                break;

            case 2:
                printf("Enter the element to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;

            case 3:
                printf("Elements (In-order traversal): ");
                inOrderTraversal(root);
                break;

            case 4:
                // Free the allocated memory before exiting
                freeTree(root);
                printf("Program terminated.\n");
                break;

            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }

    } while (choice != 4);

    return 0;
}
