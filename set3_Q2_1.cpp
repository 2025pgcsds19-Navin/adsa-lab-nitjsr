//push costly

#include<stdio.h>
#define SIZE 100

int stack1[SIZE], stack2[SIZE];
int top1 = -1, top2 = -1;
int count = 0;

void push1(int x){
	stack1[++top] = xl;
}

int pop(){
	return stack1[top1--];
}

void push2(int x){
	stack2[++top2] = x;
}

int pop2(){
	return stack2[top2--];
}

void enqueue(int x){
	while(top1 != -1){
		push2(pop2());
	}
	push1(x);
	while(top2 != -1){
		push1(pop2());
	}
	count++;
}

void dequeue(){
	if(top1 == -1){
		printf('Queue is Empty \n');
	}
	else{
		for(int i = 0; i <= top1; i++){
			printf('%d',stack1[i]);
		}
		printf('/n')
	}
}

int main(){
	enqueue(10);
	enqueue(20);
	enqueue(30);
	display();
	dequeue();
	display();
	return 0;
}
