/*The Node structure is defined as
struct Node
{
    int key;
    Node *left, *right;
}; */

namespace {
    // Function object performing recursive reverse (max to min) inorder
    // traversal by a specified number of steps, then returning the key of
    // the last node visited.
    class Traverse {
    public:
        explicit Traverse(const int count) : m_count{count} { }
        
        int operator()(const Node *root);
    
    private:
        int m_count;
    };
    
    int Traverse::operator()(const Node *const root)
    {
        static constexpr auto not_done = -1;
        
        if (root == nullptr) return not_done;
        
        const auto right = operator()(root->right);
        if (right != not_done) return right;
        
        return --m_count == 0 ? root->key : operator()(root->left);
    }
}

/*Complete the function below*/
void kthLargest(Node *root, int k)
{
    cout << Traverse{k}(root) << '\n';
}
