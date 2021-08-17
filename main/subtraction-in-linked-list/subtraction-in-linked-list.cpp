/* Structure of linked list Node
struct Node
{
    int data;
    struct Node* next;
}; 
*/

namespace {
    constexpr auto base = 10;
    
    // Returns true if borrowing occurred.
    bool subtractInPlace(Node *const minuend, const Node *const subtrahend)
    {
        if (minuend == nullptr || subtrahend == nullptr) return false;
        
        if (subtractInPlace(minuend->next, subtrahend->next)) --minuend->data;
        minuend->data -= subtrahend->data;
        
        if (minuend->data < 0) { // borrow
            minuend->data += base;
            return true;
        }
        
        return false;
    }
    
    Node* prependZeros(Node* head, int count) // note: not exception-safe
    {
        while (count-- > 0) head = new Node{0, head};
        return head;
    }
    
    void deleteTo(Node *head, Node *const tail)
    {
        while (head != tail) {
            const auto next = head->next;
            delete head;
            head = next;
        }
    }
    
    inline void swapNodes(Node*& l1, Node*& l2) // we don't have <utility>
    {
        Node* tmp = l1;
        l1 = l2;
        l2 = tmp;
    }
    
    // After swapping l1 and l2 if l1 < l2, returns len(l1) - len(l2).
    int putMinuendFirstAndGetLengthDifference(Node*& l1, Node*& l2)
    {
        auto h1 = l1, h2 = l2;
        auto comparison = 0;
        
        for (; h1 != nullptr && h2 != nullptr; h1 = h1->next, h2 = h2->next)
            if (comparison == 0) comparison = h1->data - h2->data;
        
        if (h1 == nullptr && h2 == nullptr) {
            if (comparison < 0) swapNodes(l1, l2);
            return 0;
        }
        
        if (h1 == nullptr) {
            swapNodes(l1, l2);
            swapNodes(h1, h2); // now h1 != nullptr
        }
        
        auto count = 0;
        for (; h1 != nullptr; h1 = h1->next) ++count;
        return count;
    }
}

/*You are required to complete this method*/
Node* subLinkedList(Node* l1, Node* l2)
{
    const auto gap = putMinuendFirstAndGetLengthDifference(l1, l2);
    const auto subtrahend = prependZeros(l2, gap);
    
    const bool underflow = subtractInPlace(l1, subtrahend);
    (void)underflow; // TODO: if we can use <assert>, use assert(!underflow)
    
    deleteTo(subtrahend, l2); // clean up the leaning zeros we added
    return l1;
}
