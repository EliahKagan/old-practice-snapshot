/* Link list Node 
struct Node
{
    int data;
    struct Node* next;
};*/

#include <cassert>

namespace {
    void erase(Node *head)
    {
        while (head != nullptr) {
            const auto next = head->next;
            delete head;
            head = next;
        }
    }
    
    void thin(Node *head, const int k) {
        assert(k > 1);
        
        for (const auto istart = k - 2; ; head = head->next) {
            for (auto i = istart; i != 0; --i) {
                if (head == nullptr) return;
                head = head->next;
            }
            
            if (head == nullptr) return;
            
            const auto next = head->next;
            if (next == nullptr) return;
            
            head->next = next->next;
            delete next;
        }
    }
}

/*You are required to complete this method*/
Node * deleteK(Node *const head, const int k)
{
    assert(k > 0);
    
    if (k == 1) {
        erase(head);
        return nullptr;
    }
    
    thin(head, k);
    return head;
}
