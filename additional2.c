/* Additional Exercise 2
	Reverse a singly linked list containing words in the data field using recursion.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char* data;
	struct node* next;
} node;

node* getll();
void freell(node*);
void reverse(node**);
void display(node*);

int main() {
	node* head = getll();

	display(head);

	reverse(&head);

	display(head);

	freell(head);

	return 0;
}

node* getll() {
	int n;
	printf("Enter the number of elements: ");
	scanf("%d", &n);

	node *head=NULL, *temp;
	char ele[50];

	printf("Enter the words:\n");
	for(int i=0; i<n; i++) {
		if(head == NULL)
			head = temp = (node*) malloc(sizeof(node));
		else {
			temp->next = (node*) malloc(sizeof(node));
			temp = temp->next;
		}
		scanf(" %s", ele);
		temp->data = (char*) calloc(strlen(ele)+1, sizeof(char));
		strcpy(temp->data, ele);
	}
	if(head)
		temp->next = NULL;

	return head;
}

void display(node* head) {
	if(head == NULL) {
		printf("Linked List is Empty!!!\n");
		return;
	}
	printf("Linked List Contains:");
	while(head != NULL) {
		printf("\n\t%s", head->data);
		head = head->next;
	}
	printf("\n");
}

void freell(node* head) {
	node* temp;
	while(head != NULL) {
		temp = head;
		head = head->next;
		free(temp->data);
		free(temp);
	}
}

void reverse(node** head) {
	if((*head)->next == NULL) {
		return;
	}
	node *temp = *head;
	temp->next = NULL;
	*head = (*head)->next;
	
	reverse(head);

	node *curr = *head;
	while(curr->next != NULL) 
		curr = curr->next;
	curr->next = temp;
}