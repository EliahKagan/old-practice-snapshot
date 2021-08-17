/* Linked List Node structure
   struct Node  {
     int data;
     struct Node *next;
  }
*/

// Should reverse list and return new head.
struct Node* reverse(struct Node *head)
{
    if (head != nullptr) {
        for (struct Node *prev {nullptr}; ; ) {
            const auto next = head->next;
            head->next = prev;
            
            if (next == nullptr) break;
            
            prev = head;
            head = next;
        }
    }
    
    return head;
}
