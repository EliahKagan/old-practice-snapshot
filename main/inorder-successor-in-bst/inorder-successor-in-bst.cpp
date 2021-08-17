/*The structure of Node
struct Node {
int data;
Node * right, * left;
};*/

namespace {
    Node * findInOrderSuccessor(Node *root, Node *x)
    {
        Node *prev = nullptr;
        
        const function<Node * (Node *)>
        dfs {[&dfs, &prev, x](Node *cur) -> Node * {
            if (cur == nullptr) return nullptr;
            
            if (const auto p = dfs(cur->left)) return p;
            
            if (prev == x) return cur;
            prev = cur;
            
            return dfs(cur->right);
        }};
        
        return dfs(root);
    }
}

/* The below function should return the node which is 
inorder successor of given node x. */
Node * inOrderSuccessor(Node *root, Node *x)
{
    if (root == nullptr || x == nullptr) return nullptr;
    return findInOrderSuccessor(root, x);
}
