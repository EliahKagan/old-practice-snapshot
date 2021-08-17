/* struct Node
 {
   int data;
   struct Node* next;
 }; */

#include <cassert>

/* Should return data of n'th node from the end of linked list */
int getNthFromLast(struct Node *head, int n)
{
    constexpr auto element_out_of_range = -1;
    
    assert(n > 0);
    
    auto p = head;
    for (; n != 0 && p != nullptr; --n) p = p->next;
    if (n != 0) return element_out_of_range;
    
    for (; p != nullptr; p = p->next) head = head->next;
    return head->data;
}
