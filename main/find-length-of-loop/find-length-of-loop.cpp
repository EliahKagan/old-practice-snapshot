/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*
Structure of the node of the linked list is as
struct Node
{
	int data;
	struct Node* next;
};
*/
// Your task is to complete the function this function
// function should return the size of the loop
int countNodesinLoop(struct Node *head)
{
    struct Node *cur = head;

    // Move head and cur to any (same) node in the cycle, or
    // return 0 if there is no cycle.
    do {
        if (cur == nullptr || cur->next == nullptr) return 0;
        cur = cur->next->next;
        head = head->next;
    }
    while (cur != head);

    // Go around the cycle and count how many nodes it has.
    int n = 1;
    while ((cur = cur->next) != head) ++n;
    return n;
}
