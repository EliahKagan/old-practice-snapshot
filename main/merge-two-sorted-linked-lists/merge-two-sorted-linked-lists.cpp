/*
  Merge two sorted lists A and B as one linked list
  Node is defined as 
  struct Node
  {
     int data;
     struct Node *next;
  }
*/
Node* MergeLists(Node* headA, Node* headB)
{
    if (headA == nullptr) return headB;
    if (headB == nullptr) return headA;
    
    const auto head = headB->data < headA->data ? headB : headA;
    auto p = head, q = (p == headB ? headA : headB);
    
    for (; p->next != nullptr; p = p->next) {
        const auto bound = p->next->data;
        if (bound <= q->data) continue;
        
        auto r = q;
        while (r->next != nullptr && r->next->data <= bound) r = r->next;
        
        const auto next = p->next;
        p->next = q;
        q = r->next;
        r->next = next;
        
        if (q == nullptr) return head;
    }
    
    p->next = q;
    return head;
}
