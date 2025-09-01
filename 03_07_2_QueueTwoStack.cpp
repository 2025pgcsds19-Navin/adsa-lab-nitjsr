//pop costly
#include <stdio.h>
#define size 100

int stack1[size], stack2[size];
int top1 = -1, top2 = -1;

void push1(int x) {
    stack1[++top1] = x;
}

int pop1() {
    return stack1[top1--];
}

void push2(int x) {
    stack2[++top2] = x;
}

int pop2() {
    return stack2[top2--];
}

void enqueue(int x) {
    push1(x);
}

void dequeue() {
    if (top1 == -1) {
        printf("Queue is empty\n");
    } else {
        while (top1 != -1) {
            push2(pop1());
        }
        printf("Deleted %d\n", pop2());
        while (top2 != -1) {
            push1(pop2());
        }
    }
}

void display() {
    if (top1 == -1) {
        printf("Queue is empty\n");
    } else {
        for (int i = 0; i <= top1; i++) {
            printf("%d ", stack1[i]);
        }
        printf("\n");
    }
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();
    dequeue();
    display();
    return 0;
} 


