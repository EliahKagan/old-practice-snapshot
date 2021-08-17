/* The structure of the Linked list Node is as follows:
struct Node
{
    Node* next;
    int data;
}; */

void sortList(Node** const headp)
{
    assert(headp != nullptr);
    
    for (auto cur = *headp; cur != nullptr && cur->next != nullptr; ) {
        if (cur->next->data < 0) {
            const auto head = cur->next;
            cur->next = head->next;
            head->next = *headp;
            *headp = head;
        }
        else cur = cur->next;
    }
}
