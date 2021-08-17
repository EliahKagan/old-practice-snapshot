/* Link list Node 
struct Node {
    int data;
    struct Node* next;
}; */

/* Should return data of middle node. If linked list is empty, then  -1*/
int getMiddle(struct Node *head)
{
    if (!head) return -1;
    
    for (const Node *fast = head; fast && fast->next; fast = fast->next->next)
        head = head->next;
    
    return head->data;
}

