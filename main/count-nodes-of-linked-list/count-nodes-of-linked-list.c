/*
Count the number of nodes 
in the linked list
Node is defined as 
struct node
{
    int data;
    struct node* next;
};
 
*/

int getCount(struct node* const head)
{
    return head == NULL ? 0 : 1 + getCount(head->next);
}

