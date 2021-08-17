/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*
Structure of the Node of the linked list is as
struct Node {
	int data;
	Node* next;
};
*/
// function should insert node at the middle
// of the linked list
Node* insertInMiddle(Node* const head, const int x)
{
    if (!head) return new Node{x, nullptr};

    auto* slow = head;

    for (const auto* fast = head; fast->next && fast->next->next;
                                  fast = fast->next->next)
        slow = slow->next;

    slow->next = new Node{x, slow->next};

    return head;
}
