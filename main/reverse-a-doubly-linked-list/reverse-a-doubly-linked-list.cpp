/*
   Reverse a doubly linked list, input list may also be empty
   Node is defined as
   struct Node
   {
     int data;
     Node *next;
     Node *prev;
   }
*/
Node* Reverse(Node* head)
{
    if (head == nullptr) return nullptr;

    for (; ; ) {
        std::swap(head->next, head->prev);
        if (head->prev == nullptr) break;
        head = head->prev;
    }

    return head;
}
