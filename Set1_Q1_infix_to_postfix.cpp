#include <stdio.h>
#include <ctype.h>   

#define SIZE 200   

char stack[SIZE];   
int top = -1;

void push_stack(char symbol) {
    if (top < SIZE - 1) {
        stack[++top] = symbol;
    }
}


char pstack_stack() {
    if (top == -1) return -1;
    return stack[top--];
}


char peek_stack() {
    if (top == -1) return -1;
    return stack[top];
}

int get_priority(char stack) {
    if (stack == '/' || stack == '*') return 2;
    if (stack == '+' || stack == '-') return 1;
    return 0;
}

int check_parentheses(char expr[]) {
    int temp = 0; // counter method instead of 
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(') temp++;
        else if (expr[i] == ')') {
            if (temp == 0) return 0;
            temp--;
        }
    }
    return (temp == 0);
}

void convert_to_postfix(char infix[]) {
    char *ptr = infix;
    char popped;

    printf("Postfix Expression: ");
    while (*ptr != '\0') {
        if (isalnum(*ptr)) {  
            printf("%c ", *ptr);    // stackerands directly printed
        } 
        else if (*ptr == '(') {
            push_stack(*ptr);
        } 
        else if (*ptr == ')') {
            while ((popped = pstack_stack()) != '(') {
                printf("%c ", popped);
            }
        } 
        else {  // stackerator
            while (get_priority(peek_stack()) >= get_priority(*ptr)) {
                printf("%c ", pstack_stack());
            }
            push_stack(*ptr);
        }
        ptr++;
    }

    while (top != -1) {
        printf("%c ", pstack_stack());
    }
    printf("\n");
}

int main() {
    char input[SIZE];
    printf("Enter an infix expression: ");
    scanf("%s", input);

    convert_to_postfix(input);
    return 0;
}

