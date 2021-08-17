/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for C++
/* Linked List Node structure
struct Node
{
int data;
struct Node* next;
};
*/
// Move Zeros to the front of the list
void moveZeroes(struct Node **headp)
{
    Node sentinel {0, *headp};
    auto cur = &sentinel;
    Node *nonzero {nullptr};

    while (cur->next) {
        if (cur->next->data == 0) {
            cur = cur->next;
        } else {
            const auto node = cur->next;
            cur->next = node->next;
            node->next = nonzero;
            nonzero = node;
        }
    }

    cur->next = nonzero;
    *headp = sentinel.next;
}
