/* Structure for tree and linked list
struct Node
{
    int data;

    // left is used as previous and right is used
    // as next in DLL
    Node *left, *right;
}; */

namespace {
    template<typename T>
    T dequeue(queue<T>& xs)
    {
        const auto x = xs.front();
        xs.pop();
        return x;
    }
    
    void InOrder(queue<Node *> &nodes, Node *root)
    {
        if (root != nullptr) {
            InOrder(nodes, root->left);
            nodes.push(root);
            InOrder(nodes, root->right);
        }
    }
    
    queue<Node *> InOrder(Node *const root)
    {
        queue<Node *> nodes;
        InOrder(nodes, root);
        return nodes;
    }
    
    Node *InOrderDLL(Node *const root)
    {
        auto nodes = InOrder(root);
        if (nodes.empty()) return nullptr;
        
        const auto head = dequeue(nodes);
        assert(head->left == nullptr);
        
        auto cur = head;
        
        for (; !nodes.empty(); cur = cur->right) {
            cur->right = dequeue(nodes);
            cur->right->left = cur;
        }
        
        assert(cur->right == nullptr);
        
        return head;
    }
}

// This function should convert a given Binary tree to Doubly
// Linked List
// root --> Root of Binary Tree
// head_ref --> Pointer to head node of created doubly linked list
void BToDLL(Node *const root, Node **const head_ref)
{
    assert(head_ref != nullptr);
    *head_ref = InOrderDLL(root);
}
