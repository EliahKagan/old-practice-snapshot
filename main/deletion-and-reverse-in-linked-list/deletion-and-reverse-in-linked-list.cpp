/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/* structure for a node
struct Node
{
	int data;
	struct Node *next;
};
*/
/* Function to delete a given node from the list */
void deleteNode(struct Node* const head, const int key)
{
    auto cur = head;
    while (cur->next != head && cur->next->data != key)
        cur = cur->next;

    if (cur->next == head) return;

    const auto next = cur->next;
    cur->next = next->next;
    free(next);
}

/* Function to reverse the linked list */
static void reverse(struct Node** const head_ref)
{
    const auto head = *head_ref;
    auto acc = head;

    for (auto cur = head->next; ; ) {
        const auto next = cur->next;
        cur->next = acc;
        acc = cur;

        if (cur == head) break;
        cur = next;
    }

    *head_ref = head->next;
}
