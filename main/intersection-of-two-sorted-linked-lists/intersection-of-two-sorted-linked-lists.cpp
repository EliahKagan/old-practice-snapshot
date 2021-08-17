/* The structure of the Linked list Node is as follows:
struct node {
    int val;
    struct node* next;
}; */

void intersection(struct node **head1, struct node **head2,
                  struct node **head3)
{
    struct node sentinel {0, nullptr};
    
    for (auto tail = &sentinel, p = *head1, q = *head2;
                p != nullptr && q != nullptr; ) {
        if (p->val == q->val) {
            tail->next = new (struct node){p->val, nullptr};
            tail = tail->next;
            
            p = p->next;
            q = q->next;
        }
        else if (p->val < q->val) p = p->next;
        else q = q->next;
    }
    
    *head3 = sentinel.next;
}
