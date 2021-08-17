/* Linked list node structure
struct Node
{
    int data;
    Node* next;
};*/

/*The method multiplies 
two  linked lists l1 and l2
and returns their product*/

namespace {
    constexpr auto base = 10LL, mod = 1000000007LL;
    
    long long valueOf(const Node *head)
    {
        auto acc = 0LL;
        
        for (; head != nullptr; head = head->next)
            acc = (acc * base + head->data) % mod;
        
        return acc;
    }
}

/*You are required to complete this method*/
long long multiplyTwoLists(Node* const l1, Node* const l2)
{
    return valueOf(l1) * valueOf(l2) % mod;
}
