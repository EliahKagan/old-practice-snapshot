/* a node of the doubly linked list */
/*struct node
{
    int data;
    struct node *next;
    struct node *prev;
};
   struct node *lastNode(struct node *root)
{
    while (root && root->next)
        root = root->next;
    return root;
}
void _quickSort(struct node* l, struct node *h)
{
    if (h != NULL && l != h && l != h->next)
    {
        struct node *p = partition(l, h);
        _quickSort(l, p->prev);
        _quickSort(p->next, h);
    }
}
 
void quickSort(struct node *head)
{
    // Find last node
    struct node *h = lastNode(head);
 
    // Call the recursive QuickSort
    _quickSort(head, h);
}*/

static inline void swap_data(struct node *const p, struct node *const q)
{
    const int tmp = p->data;
    p->data = q->data;
    q->data = tmp;
}

// Lomuto partition scheme
struct node *partition(struct node *low, struct node *const high)
{
    const int pivot = high->data;
    
    for (struct node *cur = low; cur != high; cur = cur->next) {
        if (cur->data < pivot) {
            swap_data(low, cur);
            low = low->next;
        }
    }
    
    swap_data(low, high);
    return low;
}
