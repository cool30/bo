#include <stdio.h>
#include <stdlib.h>

// Define a structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function prototypes
struct TreeNode *constructBT(int pre[], int post[], int *preIndex, int start, int end, int size);
struct TreeNode *createNode(int data);
void printInOrder(struct TreeNode *root);

// Function to construct a binary tree from pre-order and post-order traversal
struct TreeNode *constructBT(int pre[], int post[], int *preIndex, int start, int end, int size) {
    if (*preIndex >= size || start > end) {
        return NULL;
    }

    struct TreeNode *root = createNode(pre[*preIndex]);
    (*preIndex)++;

    if (start == end) {
        return root;
    }

    int postIndex;
    for (postIndex = start; postIndex <= end; postIndex++) {
        if (post[postIndex] == pre[*preIndex]) {
            break;
        }
    }

    if (postIndex <= end) {
        root->left = constructBT(pre, post, preIndex, start, postIndex, size);
        root->right = constructBT(pre, post, preIndex, postIndex + 1, end, size);
    }

    return root;
}

// Function to create a new node
struct TreeNode *createNode(int data) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to print in-order traversal of a binary tree
void printInOrder(struct TreeNode *root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->data);
        printInOrder(root->right);
    }
}

// Main function
int main() {
    int pre[] = {1, 2, 4, 8, 9, 5, 3, 6, 7};
    int post[] = {8, 9, 4, 5, 2, 6, 7, 3, 1};
    int size = sizeof(pre) / sizeof(pre[0]);

    int preIndex = 0;
    struct TreeNode *root = constructBT(pre, post, &preIndex, 0, size - 1, size);

    printf("In-order traversal of the constructed Binary Tree: ");
    printInOrder(root);
    printf("\n");

    // Free the allocated memory before exiting
    // (You can implement a separate function to free the tree nodes)
    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right->left);
    free(root->right->right);
    free(root->right);
    free(root);

    return 0;
}
