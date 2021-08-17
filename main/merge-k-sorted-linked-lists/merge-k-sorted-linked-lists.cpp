/*Linked list node structure
struct node
{
    int data;
    struct node* next;
};*/ 

namespace {
    node *merge(node *head1, node *head2)
    {
        node start {0, nullptr}, *cur = &start;
        
        for (; head1 != nullptr && head2 != nullptr; cur = cur->next) {
            if (head1->data < head2->data) {
                cur->next = head1;
                head1 = head1->next;
            } else {
                cur->next = head2;
                head2 = head2->next;
            }
        }
        
        cur->next = (head1 == nullptr ? head2 : head1);
        return start.next;
    }
}

/* a[] is an array of pointers to heads of linked lists
  and n is size of a[]  */
node *mergeKList(node **const a, const int n)
{
    node *acc {nullptr};
    for (auto i = 0; i != n; ++i) acc = merge(acc, a[i]);
    return acc;
}
