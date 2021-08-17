/*
Please note that it's Function problem i.e.
you need to write your solution in the form Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*
Structure of the node of the binary tree
struct Node
{
	int data;
	struct Node *next;
};
*/
// Complete this function
void deleteAlt(struct Node *head)
{
    for (; head != nullptr && head->next != nullptr; head = head->next) {
        const auto next = head->next;
        head->next = next->next;
        free(next); // it was allocated with malloc()
    }
}
