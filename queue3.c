#include <stdio.h>
#include <stdlib.h>

// Define a structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function prototypes
struct TreeNode* createNode(int key);
void printAncestors(struct TreeNode* root, int key);

// Function to create a new node
struct TreeNode* createNode(int key) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to print ancestors of a key in a binary tree
void printAncestors(struct TreeNode* root, int key) {
    if (root == NULL) {
        return;
    }

    if (root->data == key) {
        // Key is found, no need to go further
        return;
    }

    if ((root->left != NULL && root->left->data == key) ||
        (root->right != NULL && root->right->data == key)) {
        // Key is a child of the current root
        printf("%d ", root->data);
        return;
    }

    // Check in the left and right subtrees
    if (key < root->data) {
        printAncestors(root->left, key);
    } else {
        printAncestors(root->right, key);
    }

    // If key is found in either subtree, print the current root
    if ((root->left != NULL && root->left->data == key) ||
        (root->right != NULL && root->right->data == key)) {
        printf("%d ", root->data);
    }
}

// Main function
int main() {
    struct TreeNode* root = createNode(50);
    root->left = createNode(30);
    root->right = createNode(70);
    root->left->left = createNode(20);
    root->left->right = createNode(40);
    root->right->left = createNode(60);
    root->right->right = createNode(80);

    int keyToFind = 40;

    printf("Ancestors of %d: ", keyToFind);
    printAncestors(root, keyToFind);
    printf("\n");

    // Free the allocated memory before exiting
    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
