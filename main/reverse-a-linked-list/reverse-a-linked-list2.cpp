/* Linked List Node structure
   struct Node  {
     int data;
     struct Node *next;
  }
*/

namespace {
    Node *rev(Node *acc, Node *node)
    {
        while (node != nullptr) {
            const auto head = node;
            node = node->next;
            head->next = acc;
            acc = head;
        }
        
        return acc;
    }
}

// Should reverse list and return new head.
Node* reverse(Node *head)
{
    return rev(nullptr, head);
}
