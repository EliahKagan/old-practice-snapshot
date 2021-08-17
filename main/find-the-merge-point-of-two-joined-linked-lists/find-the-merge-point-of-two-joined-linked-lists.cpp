/*
   Find merge point of two linked lists
   Node is defined as
   struct Node
   {
       int data;
       Node* next;
   }
*/

namespace {
    std::size_t CountNodes(Node *head) // assumes non-empty list
    {
        std::size_t i {1u};
        for (; head->next != nullptr; head = head->next) ++i;
        return i;
    }
    
    Node *Walk(Node *head, std::size_t count) // assumes count is in bounds
    {
        for (; count != 0u; --count) head = head->next;
        return head;
    }
}

int FindMergeNode(Node *headA, Node *headB)
{
    auto a_count = CountNodes(headA), b_count = CountNodes(headB);
    if (a_count < b_count) {
        std::swap(a_count, b_count);
        std::swap(headA, headB);
    }
    
    headA = Walk(headA, a_count - b_count);
    while (headA != headB) {
        headA = headA->next;
        headB = headB->next;
    }
    
    return headA->data;
}
