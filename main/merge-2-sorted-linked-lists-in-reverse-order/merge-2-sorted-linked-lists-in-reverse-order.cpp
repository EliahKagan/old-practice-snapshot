/*

The structure of linked list is the following

struct Node
{
int data;
Node* next;
};

*/

namespace {
    inline void revStep(Node *&acc, Node *&node)
    {
        const auto head = node;
        node = node->next;
        head->next = acc;
        acc = head;
    }
    
    Node *rev(Node *acc, Node *node)
    {
        while (node != nullptr) revStep(acc, node);
        return acc;
    }
}

Node *mergeResult(Node *node1, Node *node2)
{
    Node *acc {nullptr};
    
    while (node1 != nullptr && node2 != nullptr)
        revStep(acc, (node1->data < node2->data ? node1 : node2));
    
    return rev(acc, (node1 == nullptr ? node2 : node1));
}
