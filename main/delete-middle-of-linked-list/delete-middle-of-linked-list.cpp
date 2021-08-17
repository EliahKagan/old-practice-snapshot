/* Link list Node 
struct Node
{
    int data;
    struct Node* next;
}; */

namespace {
    int getLength(const Node *head)
    {
        auto len = 0;
        for (; head != nullptr; head = head->next) ++len;
        return len;
    }
}

// Deletes middle of linked list and returns head of the modified list
Node* deleteMid(Node *const head)
{
    const auto len = getLength(head);
    
    if (len < 2) {
        if (len != 0) delete head;
        return nullptr;
    }
    
    auto cur = head;
    for (auto i = len / 2; --i != 0; ) cur = cur->next;
    
    const auto next = cur->next;
    cur->next = next->next;
    delete next;
    
    return head;
}
