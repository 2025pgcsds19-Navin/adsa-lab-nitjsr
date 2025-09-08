#include <stdio.h>
#include <stdlib.h>

// Node definition
struct Node {
    int key;
    struct Node *left, *right;
    int height;
};

// Utility: max of two
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Get height of a node
int getHeight(struct Node *n) {
    if (n == NULL) return 0;
    return n->height;
}

// Get balance factor of a node
int getBalance(struct Node *n) {
    if (n == NULL) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

// Create new node
struct Node* createNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // leaf node has height = 1
    return node;
}

// Create empty tree
struct Node* createTree() {
    return NULL;
}

// Right rotation
struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Rotate
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // new root
}

// Left rotation
struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Rotate
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // new root
}

// Insert key (AVL balancing)
struct Node* insertItem(struct Node* node, int key) {
    if (node == NULL) return createNode(key);

    if (key < node->key)
        node->left = insertItem(node->left, key);
    else if (key > node->key)
        node->right = insertItem(node->right, key);
    else
        return node; // no duplicates

    // Update height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Balance factor
    int balance = getBalance(node);

    // Balance cases
    // Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // unchanged
}

// Minimum value node (used in delete)
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete a key
struct Node* deleteItem(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteItem(root->left, key);
    else if (key > root->key)
        root->right = deleteItem(root->right, key);
    else {
        // node with one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) { // no child
                temp = root;
                root = NULL;
            } else { // one child
                *root = *temp;
            }
            free(temp);
        } else {
            // two children
            struct Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteItem(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    // Update height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Balance factor
    int balance = getBalance(root);

    // Balance cases
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search key
struct Node* searchItem(struct Node* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (key < root->key) return searchItem(root->left, key);
    return searchItem(root->right, key);
}

// Delete entire tree
void deleteTree(struct Node* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// Traversals
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

// Driver
int main() {
    struct Node* root = createTree();

    root = insertItem(root, 10);
    root = insertItem(root, 20);
    root = insertItem(root, 30);
    root = insertItem(root, 40);
    root = insertItem(root, 50);
    root = insertItem(root, 25);

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    root = deleteItem(root, 40);

    printf("After deleting 40, Inorder: ");
    inorder(root);
    printf("\n");

    struct Node* found = searchItem(root, 25);
    if (found) printf("Search: 25 found\n");
    else printf("Search: 25 not found\n");

    deleteTree(root);
    return 0;
}

