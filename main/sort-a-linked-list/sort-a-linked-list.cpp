/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/* Structure of the linked list node is as
struct node
{
	int data;
	struct node* next;
};
*/

/* split the nodes of the given list into front and back halves,
     and return the two lists using the reference parameters.*/
void splitList(struct node* source, struct node** const frontRef,
                                    struct node** const backRef)
{
    *frontRef = source;

    for (auto fast = source->next; fast && fast->next; fast = fast->next->next)
        source = source->next;

    *backRef = source->next;
    source->next = nullptr;
}

// merges two sorted list into one big list
struct node* mergeList(struct node* a, struct node* b)
{
    if (!a) return b;
    if (!b) return a;

    auto head = a;
    if (a->data <= b->data) {
        a = a->next;
    } else {
        head = b;
        b = b->next;
    }

    auto cur = head;
    for (; a && b; cur = cur->next) {
        if (a->data <= b->data) {
            cur->next = a;
            a = a->next;
        } else {
            cur->next = b;
            b = b->next;
        }
    }

    cur->next = (a ? a : b);
    return head;
}
