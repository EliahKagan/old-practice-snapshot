/*The structure of linked list is the following
struct node
{
int data;
node* next;
};*/
int detectloop(struct node *const list)
{
    if (list == NULL || list->next == NULL) return 0;
    
    for (const struct node *slow = list->next, *fast = slow->next;
            fast != NULL && fast->next != NULL;
            slow = slow->next, fast = fast->next->next)
        if (fast == slow) return 1;
    
    return 0;
}
