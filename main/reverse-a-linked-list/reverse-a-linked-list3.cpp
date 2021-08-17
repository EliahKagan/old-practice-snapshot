/* Linked List Node structure
   struct Node  {
     int data;
     struct Node *next;
  }
*/

namespace {
    inline void rev_step(Node *&acc, Node *&node)
    {
        const auto head = node;
        node = node->next;
        head->next = acc;
        acc = head;
    }
    
    Node *rev(Node *acc, Node *node)
    {
        while (node != nullptr) rev_step(acc, node);
        return acc;
    }
}

// Should reverse list and return new head.
Node* reverse(Node *head)
{
    return rev(nullptr, head);
}
