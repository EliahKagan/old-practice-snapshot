/*The structure of linked list is the following
struct Node
{
int data;
Node* next;
};*/
Node *removeDuplicates(Node *const head)
{
    for (auto cur = head; cur != nullptr && cur->next != nullptr; ) {
        if (cur->data == cur->next->data) {
            const auto next = cur->next;
            cur->next = next->next;
            delete next;
        }
        else cur = cur->next;
    }
    
    return head;
}
