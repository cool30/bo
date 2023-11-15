#include <stdio.h>
#include <stdlib.h>

// Define a structure for a BST node
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function prototypes
struct TreeNode* insertNode(struct TreeNode* root, int key);
struct TreeNode* findInOrderSuccessor(struct TreeNode* root, struct TreeNode* node);

// Function to create a BST (Recursive)
struct TreeNode* insertNode(struct TreeNode* root, int key) {
    if (root == NULL) {
        struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newNode->data = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (key < root->data) {
        root->left = insertNode(root->left, key);
    } else if (key > root->data) {
        root->right = insertNode(root->right, key);
    }

    return root;
}

// Function to find the in-order successor of a node (Recursive)
struct TreeNode* findInOrderSuccessor(struct TreeNode* root, struct TreeNode* node) {
    if (root == NULL || node == NULL) {
        return NULL;
    }

    // If the right subtree of the node is not null,
    // the successor is the leftmost node in the right subtree.
    if (node->right != NULL) {
        return findMin(node->right);
    }

    // If the right subtree is null, the successor is
    // the lowest ancestor whose left child is also an ancestor of the node.
    struct TreeNode* successor = NULL;
    while (root != NULL) {
        if (node->data < root->data) {
            successor = root;
            root = root->left;
        } else if (node->data > root->data) {
            root = root->right;
        } else {
            break;
        }
    }

    return successor;
}

// Function to find the node with the minimum value in a BST
struct TreeNode* findMin(struct TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Main function
int main() {
    struct TreeNode* root = NULL;
    int keys[] = {15, 8, 20, 5, 10, 17, 25};

    // Insert elements into the BST
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); ++i) {
        root = insertNode(root, keys[i]);
    }

    // Find the in-order successor for a specific node (e.g., node with key 10)
    int keyToFind = 10;
    struct TreeNode* nodeToFind = NULL;
    struct TreeNode* current = root;

    while (current != NULL) {
        if (keyToFind < current->data) {
            current = current->left;
        } else if (keyToFind > current->data) {
            current = current->right;
        } else {
            nodeToFind = current;
            break;
        }
    }

    if (nodeToFind != NULL) {
        struct TreeNode* successor = findInOrderSuccessor(root, nodeToFind);

        if (successor != NULL) {
            printf("In-order successor of %d is %d\n", nodeToFind->data, successor->data);
        } else {
            printf("No in-order successor found for %d\n", nodeToFind->data);
        }
    } else {
        printf("Node with key %d not found in the BST.\n", keyToFind);
    }

    // Free the allocated memory before exiting
    free(root);

    return 0;
}
