//circular queue using linked list
#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct Node *front = NULL, *rear = NULL;

void enqueue(int x){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    if(front == NULL){
        front = rear = newNode;
        rear->next = front;
    }
    else{
        rear->next = newNode;
        rear = newNode;
        rear->next = front;
    }
}

void dequeue(){
    if(front == NULL){
        printf("Queue is Empty\n");
    }
    else if(front == rear){
        printf("Deleted: %d\n", front->data);
        free(front);
        front = rear = NULL;
    }
    else{
        struct Node* temp = front;
        printf("Deleted: %d\n", front->data);
        front = front->next;
        rear->next = front;
        free(temp);
    }
}

void display(){
    if(front == NULL){
        printf("Queue is Empty\n");
    }
    else{
        struct Node* temp = front;
        do{
            printf("%d ", temp->data);
            temp = temp->next;
        } while(temp != front);
        printf("\n");
    }
}


