#include <stdio.h>
#include <stdlib.h>

#define MAX 3  

struct BPlusNode {
    int val[MAX + 1], count;
    struct BPlusNode *child[MAX + 2];
    struct BPlusNode *next;
    int isLeaf;
};

struct BPlusNode *root = NULL;

struct BPlusNode* createNode(int leaf) {
    struct BPlusNode *node = (struct BPlusNode*)malloc(sizeof(struct BPlusNode));
    node->isLeaf = leaf;
    node->count = 0;
    node->next = NULL;
    for (int i = 0; i <= MAX + 1; i++) node->child[i] = NULL;
    return node;
}

void insertLeaf(struct BPlusNode *leaf, int val) {
    int i = leaf->count - 1;
    while (i >= 0 && leaf->val[i] > val) {
        leaf->val[i + 1] = leaf->val[i];
        i--;
    }
    leaf->val[i + 1] = val;
    leaf->count++;
}

void splitLeaf(struct BPlusNode *leaf, int val, struct BPlusNode **newLeaf, int *pval) {
    int temp[MAX + 2];
    for (int i = 0; i < leaf->count; i++) temp[i] = leaf->val[i];
    int i = leaf->count - 1;
    while (i >= 0 && temp[i] > val) {
        temp[i + 1] = temp[i];
        i--;
    }
    temp[i + 1] = val;
    int total = leaf->count + 1;
    int split = total / 2;

    *newLeaf = createNode(1);
    leaf->count = split;
    (*newLeaf)->count = total - split;

    for (i = 0; i < leaf->count; i++) leaf->val[i] = temp[i];
    for (i = 0; i < (*newLeaf)->count; i++) (*newLeaf)->val[i] = temp[i + split];

    (*newLeaf)->next = leaf->next;
    leaf->next = *newLeaf;
    *pval = (*newLeaf)->val[0];
}

void insertInternal(struct BPlusNode **node, int val, struct BPlusNode *child) {
    if (*node == NULL) return;
    if ((*node)->isLeaf) return;

    int i = (*node)->count - 1;
    while (i >= 0 && val < (*node)->val[i]) i--;
    i++;

    if ((*node)->child[i]->count == MAX) {
        if ((*node)->child[i]->isLeaf) {
            struct BPlusNode *newLeaf;
            int pval;
            splitLeaf((*node)->child[i], val, &newLeaf, &pval);

            for (int j = (*node)->count; j > i; j--) {
                (*node)->val[j] = (*node)->val[j - 1];
                (*node)->child[j + 1] = (*node)->child[j];
            }
            (*node)->val[i] = pval;
            (*node)->child[i + 1] = newLeaf;
            (*node)->count++;
        }
    } else {
        if ((*node)->child[i]->isLeaf) {
            insertLeaf((*node)->child[i], val);
        }
    }
}

void insert(int val) {
    if (root == NULL) {
        root = createNode(1);
        root->val[0] = val;
        root->count = 1;
        return;
    }
    if (root->isLeaf) {
        if (root->count < MAX) {
            insertLeaf(root, val);
        } else {
            struct BPlusNode *newLeaf;
            int pval;
            splitLeaf(root, val, &newLeaf, &pval);
            struct BPlusNode *newRoot = createNode(0);
            newRoot->val[0] = pval;
            newRoot->child[0] = root;
            newRoot->child[1] = newLeaf;
            newRoot->count = 1;
            root = newRoot;
        }
    } else {
        insertInternal(&root, val, NULL);
    }
}

struct BPlusNode* search(int val) {
    struct BPlusNode *node = root;
    while (node && !node->isLeaf) {
        int i;
        for (i = 0; i < node->count && val >= node->val[i]; i++);
        node = node->child[i];
    }
    return node;
}

void traversal(struct BPlusNode *node) {
    while (node) {
        for (int i = 0; i < node->count; i++) printf("%d ", node->val[i]);
        node = node->next;
    }
}

int main() {
    insert(5);
    insert(15);
    insert(25);
    insert(35);
    insert(45);
    insert(55);
    insert(65);
    insert(75);

    printf("B+ Tree Traversal:\n");
    traversal(root->isLeaf ? root : root->child[0]);
    printf("\n");

    int key = 25;
    struct BPlusNode* found = search(key);
    if (found) {
        int ok = 0;
        for (int i = 0; i < found->count; i++) {
            if (found->val[i] == key) ok = 1;
        }
        if (ok) printf("Key %d found in leaf.\n", key);
        else printf("Key %d not found.\n", key);
    }

    return 0;
}

