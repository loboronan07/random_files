/* Lab Exercise 3
	Write a program to check whether given string is a palindrome using a dequeue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char* arr;
	int front;
	int rear;
	int size;
} dequeue;

int isPalin(char *);
void insert(dequeue *, char);
char delete(dequeue *, int);
void freeq(dequeue *);

int main() {
	char str[100];

	printf("Enter a Sting: ");
	scanf("%[^\n]s", str);

	if(isPalin(str)) 
		printf("The entered string is a palindrome...\n");
	else 
		printf("The entered string is not a palindrome...\n");

	return 0;
}

int isPalin(char* str) {
	dequeue* q = (dequeue*) malloc(sizeof(dequeue));
	q->size = strlen(str) + 1;
	q->front = q->rear = 0;
	q->arr = (char*) calloc(q->size, sizeof(char));

	while(*str != '\0') 
		insert(q, *(str++));

	int flag = 1;
	char f, r;
	f = delete(q, 0);
	r = delete(q, 1);
	while(f != '\0' || r != '\0') {
		if(f != r) {
			flag = 0;
			break;
		}
		f = delete(q, 0);
		r = delete(q, 1);
	}

	freeq(q);
	
	return flag;
}

void insert(dequeue *q, char ele) {
	if((q->rear+1) % q->size == q->front) {
		printf("Queue Full\n");
		return;
	}
	q->rear = (q->rear+1) % q->size;
	q->arr[q->rear] = ele;
}

char delete(dequeue *q, int i) {
	char x;
	if(q->front == q->rear) {
		x = '\0';
	}
	else if((q->front+1) % q->size == q->rear) {
		x = q->arr[q->rear];
		q->front = q->rear = 0;
	}
	else {
		if(!i) {
			q->front = (q->front+1) % q->size;
			x = q->arr[q->front];
		}
		else {
			x = q->arr[q->rear];
			q->rear = (q->rear-1 >= 0) ? q->rear-1 : q->size-1;
		}
	}
	return x;
}

void freeq(dequeue* q) {
	free(q->arr);
	free(q);
}
