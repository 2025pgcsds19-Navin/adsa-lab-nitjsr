#include <stdio.h>  // For input/output
#include <stdlib.h> // For malloc and free

// Define node structure
struct Linked_List {
    int data;              // Data value
    struct Linked_List* next; // Pointer to next node
};

// Function decleration
void insert(struct Linked_List** head, int value);
void delete_by_value(struct Linked_List** head, int value);
void search_by_value(struct Linked_List* head, int value);
void traverse_list(struct Linked_List* head);

int main() {
    struct Linked_List* head = NULL; // Initialize head to NULL
    int choice, value;              // For menu choice and input value
    
    // Menu-driven loop
    while (1) {
        printf("\n--- Linked List Menu ---\n");
        printf("1. Insert value \n");
        printf("2. Delete value\n");
        printf("3. Search value \n");
        printf("4. Display list \n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(&head, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                delete_by_value(&head, value);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                search_by_value(head, value);
                break;
            case 4:
                traverse_list(head);
                break;
            case 5:
                printf("Exiting program.\n");
                // Free memory before exit
                while (head != NULL) {
                    struct Linked_List* temp = head;
                    head = head->next;
                    free(temp);
                }
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    
    return 0;
}

// Insert 
void insert(struct Linked_List** head, int value) {
    struct Linked_List* new_node = (struct Linked_List*)malloc(sizeof(struct Linked_List));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    new_node->data = value;
    new_node->next = NULL;
    
    if (*head == NULL) {
        *head = new_node; // First node
    } else {
        struct Linked_List* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next; // Traverse to last node
        }
        temp->next = new_node; // Append new node
    }
    printf("Value %d inserted.\n", value);
}

// Delete node by value
void delete_by_value(struct Linked_List** head, int value) {
    struct Linked_List* temp = *head;
    struct Linked_List* prev = NULL;
    
    if (temp != NULL && temp->data == value) { //if elements is found on first place t
        *head = temp->next;
        free(temp);
        printf("Value %d deleted.\n", value);
        return;
    }
    
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Value %d not found!\n", value);
        return;
    }
    
    prev->next = temp->next;
    free(temp);
    printf("Value %d deleted.\n", value);
}

// Search for value
void search_by_value(struct Linked_List* head, int value) {
    struct Linked_List* temp = head;
    int position = 1;
    
    while (temp != NULL) {
        if (temp->data == value) {
            printf("Value %d found at position %d.\n", value, position);
            return;
        }
        temp = temp->next;
        position++;
    }
    printf("Value %d not found!\n", value);
}

// Display the list
void traverse_list(struct Linked_List* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    printf("List elements: ");
    struct Linked_List* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);	
        temp = temp->next;
    }
    printf("\n");
}
