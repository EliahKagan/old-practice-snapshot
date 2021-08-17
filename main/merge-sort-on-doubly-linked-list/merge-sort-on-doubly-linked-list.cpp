/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/*
Structure of the node of the list is as
struct node
{
	int data;
	struct node *next, *prev;
};
*/

// Split a doubly linked list (DLL) into 2 DLLs of
// half sizes
struct node *splitList(struct node *head)
{
    for (auto fast = head->next; fast && fast->next; fast = fast->next->next)
        head = head->next;

    const auto ret = head->next;
    head->next = nullptr;
    if (ret) ret->prev = nullptr;
    return ret;
}

// Function to merge two DLLs
struct node *merge(struct node *first, struct node *second)
{
    struct node sentinel {0, nullptr, nullptr};

    auto cur = &sentinel;
    while (first && second) {
        if (first->data <= second->data) {
            first->prev = cur;
            cur = cur->next = first;
            first = first->next;
        } else {
            second->prev = cur;
            cur = cur->next = second;
            second = second->next;
        }
    }

    if (first) {
        first->prev = cur;
        cur->next = first;
    } else {
        second->prev = cur;
        cur->next = second;
    }

    sentinel.next->prev = nullptr;
    return sentinel.next;
}
