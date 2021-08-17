/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/*structure of the node of the DLL is as
struct Node {
	int data;
	struct Node* prev, *next;
};
*/
// function should insert a new node in sorted way in
// a sorted doubly linked list
void sortedInsert(struct Node** head_ref, struct Node* newNode)
{
    struct Node sentinel {0, nullptr, *head_ref};
    if (sentinel.next) sentinel.next->prev = &sentinel;

    auto cur = &sentinel;
    while (cur->next && cur->next->data < newNode->data) cur = cur->next;

    newNode->prev = cur;
    newNode->next = cur->next;
    if (cur->next) cur->next->prev = newNode;
    cur->next = newNode;

    sentinel.next->prev = nullptr;
    *head_ref = sentinel.next;
}
