/* The structure of linked list is the following
struct Node
{
   int data;
   Node* next;
};   */

namespace {
    int getLength(const Node *const head)
    {
        if (head == nullptr) return 0;
        
        auto count = 1;
        for (auto cur = head->next; cur != head; cur = cur->next) ++count;
        return count;
    }
    
    Node *advance(Node *head, int length)
    {
        for (; length > 0; --length) head = head->next;
        return head;
    }
    
    // Splits a circular linked list after the first length elements,
    // returning the the head node of the newly created second list
    // (i.e., the (length + 1)th node).
    Node *split(Node *head, int length)
    {
        const auto prev = advance(head, length - 1);
        const auto ret = prev->next;
        prev->next = head;
        
        auto next = ret;
        while (next->next != head) next = next->next;
        next->next = ret;
        
        return ret;
    }
}

//  function which splits the circular linked list.  head is pointer
// to head Node of given lined list.  head1_ref1 and *head_ref2
// are pointers to head pointers of resultant two halves.
void splitList(Node *const head, Node **const head1_ref,
                                 Node **const head2_ref)
{
    const auto length = getLength(head);
    *head2_ref = (length < 2 ? nullptr : split(head, (length + 1) / 2));
    *head1_ref = head;
}
