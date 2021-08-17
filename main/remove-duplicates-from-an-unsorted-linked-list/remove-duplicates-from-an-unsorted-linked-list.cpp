/*

The structure of linked list is the following

struct Node
{
int data;
Node* next;
};

*/


Node *removeDuplicates(Node *const head)
{
    if (head == nullptr) return nullptr;
    
    unordered_set<decltype(head->data)> s {head->data};
    
    for (auto cur = head; cur->next != nullptr; ) {
        if (s.find(cur->next->data) == s.end()) {
            s.insert(cur->next->data);
            cur = cur->next;
        } else {
            const auto next = cur->next;
            cur->next = next->next;
            delete next;
        }
    }
    
    return head;
}
