/* structure for a node 
struct Node
{
    int data;
    struct Node *next;
}; */

/* Function to print nodes in a given Circular linked list */
void printList(struct Node *const head)
{
    const struct Node *cur = head;
    do {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    while (cur != head);
}
