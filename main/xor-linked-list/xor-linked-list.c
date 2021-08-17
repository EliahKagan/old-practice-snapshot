#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Node
{
	int data;
	struct Node* npx;
};

struct Node* XOR (struct Node *a, struct Node *b)
{
	return (struct Node*) ((uintptr_t) (a) ^ (uintptr_t) (b));
}

void insert(struct Node **head_ref, int data);

void printList (struct Node *head);

// Driver program to test above functions
int main ()
{
    int t;
    scanf("%d", &t);
    while(t--){
        struct Node *head = NULL;
        int n, tmp;
        scanf("%d", &n);
        while(n--){
            scanf("%d", &tmp);
            insert(&head, tmp);
        }
        printList (head);
        printf("\n");
    }
	return (0);
}
/*
Structure of linked list is as
struct Node
{
	int data;
	struct Node* npx; 
};

Utility function to get XOR of two Struct Node pointer
use this function to get XOR of two pointers 
struct Node* XOR (struct Node *a, struct Node *b)
{
	return (struct Node*) ((uintptr_t) (a) ^ (uintptr_t) (b));
}
*/

static struct Node *makeNode(const int data, struct Node* const npx)
{
    struct Node *const p = malloc(sizeof *p);
    if (p == NULL) abort();
    
    p->data = data;
    p->npx = npx;
    
    return p;
}

// function should insert the data to the front of the list
void insert(struct Node **const head_ref, const int data)
{
    struct Node *const second = *head_ref;
    struct Node *const first = makeNode(data, XOR(NULL, second));

    if (second != NULL) {
        struct Node *const third = XOR(NULL, second->npx);
        second->npx = XOR(first, third);
    }

    *head_ref = first;
}

// Prints the list one way. Assumes head points to the first or last node.
// Returns the node at the other end.
static struct Node *printOneWay(struct Node *head)
{
    struct Node *prev = NULL;
    
    while (head != NULL) {
        printf("%d ", head->data);
        
        struct Node *const next = XOR(prev, head->npx);
        prev = head;
        head = next;
    }
    
    return prev;
}

// function should prints the contents of doubly linked list
// first in forward direction and then in backward direction
// you should print a next line after printing in forward direction
void printList(struct Node *head)
{
    head = printOneWay(head);   // front to back
    putchar('\n');
    printOneWay(head);          // back to front
}
