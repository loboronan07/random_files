/* Exercise 4
    Create a singly linked list for storing student information(name,roll,marks) and identify the second
    highest marks of a student after sorting appropriately and display his/her details.
    Sample output:
        {Arun,12,45}->{Ram,6,89}->{Raju,1,60}
        Sorted list based on marks:
        {Ram,6,89}->{ Raju,1,60}-> {Arun,12,45}
        Second highest:
        Raju,1,60
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char* name;
    int roll;
    int marks;
    struct node* next;
} node;

node* get_list();
void sort(node**);
node* second_highest(node*);
void display(node*);
void free_list(node*);

int main(void) {
    node* head = get_list();

    printf("Before Sorting: ");
    display(head);

    sort(&head);

    printf("After Sorting: ");
    display(head);

    node* second = second_highest(head);

    if(second) {
        printf("Second Highest: %s, %d, %d\n", second->name, second->roll, second->marks);
    }
    else {
        printf("Not enought nodes present in the list...\n");
    }
    free_list(head);

    return 0;
}

node* get_list() {
    int n;
    char name[50];
    
    node *head, *temp;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        if(!head) {
            head = temp = (node*) malloc(sizeof(node));
        }
        else {
            temp->next = (node*) malloc(sizeof(node));
            temp = temp->next;
        }
        printf("Student %d:\n", i+1);
        printf("\tName: ");
        scanf(" %[^\n]s", name);
        temp->name = (char*) calloc(strlen(name) + 1, sizeof(char));
        strcpy(temp->name, name);
        printf("\tRoll No: ");
        scanf("%d", &temp->roll);
        printf("\tMarks: ");
        scanf("%d", &temp->marks);
    }
    temp->next = NULL;

    return head;
}

void sort(node** head) {
    node *large=NULL, *curr=NULL, *pivot=NULL, *prev_piv=NULL;
    node *prev_large=NULL, *prev=NULL;
    pivot = *head;
    while(pivot != NULL) {
        prev_large = pivot;
        large = pivot;
        prev = pivot;
        curr = pivot->next;
        while(curr != NULL) {
            if(large->marks < curr->marks) {
                prev_large = prev;
                large = curr;
            }
            prev =  curr;
            curr = curr->next;
        }

        if(pivot != large) {
            prev_large->next = large->next;
            large->next = pivot;
            if(pivot == *head) {
                *head = large;
            }
            else {
                prev_piv->next = large;
            }
            prev_piv = large;
        }
        else {
            prev_piv = pivot;
            pivot = pivot->next;
        }
    }
}

node* second_highest(node* head) {
    return head->next;
}

void display(node* list) {
    while(list != NULL) {
        printf("{%s, %d, %d}", list->name, list->roll, list->marks);
        list = list->next;
        if(list != NULL) {
            printf("  ->  ");
        }
    }
    printf("\n");
}

void free_list(node* list) {
    node* temp;
    while(list != NULL) {
        temp = list;
        list = list->next;
        free(temp->name);
        free(temp);
    }
}