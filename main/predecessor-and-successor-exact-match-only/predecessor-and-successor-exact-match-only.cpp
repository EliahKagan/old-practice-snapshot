/*
Please note that it's Function problem i.e.
you need to write your solution in the form Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/* BST Node
struct Node
{
	int key;
	struct Node *left, *right;
};
*/

namespace {
    constexpr auto debug_traversal = true;
    
    // The tree is small (max 100 nodes), so I will disregard the constraint
    // that it is a BST and just traverse in order to the element.
    class InOrder {
    public:
        explicit InOrder(Node* root, int key) noexcept;
        
        Node* pre() const noexcept { return pre_; }
        Node* suc() const noexcept { return suc_; }
    
    private:
        void dfs(Node* root) noexcept;
    
        Node* pre_ {nullptr}, * cur_ {nullptr}, * suc_ {nullptr};
        int key_;
    };
    
    void InOrder::dfs(Node* const root) noexcept
    {
        if (root == nullptr || suc_ != nullptr) return;
        
        dfs(root->left);
        if (suc_ != nullptr) return;
        
        if (debug_traversal) cout << root->key << ' ';
        
        if (cur_ != nullptr) suc_ = root;
        else if (root->key == key_) cur_ = root;
        else pre_ = root;
        
        dfs(root->right);
    }
    
    InOrder::InOrder(Node* const root, const int key) noexcept : key_{key}
    {
        if (debug_traversal) cout << "[ ";
        
        dfs(root);
        if (cur_ == nullptr) pre_ = nullptr;
        
        if (debug_traversal) cout << "]\n";
    }
}

// This function finds predecessor and successor of key in BST.
// It sets pre and suc as predecessor and successor respectively
void findPreSuc(Node* const root, Node*& pre, Node*& suc, const int key)
{
    InOrder trav {root, key};
    pre = trav.pre();
    suc = trav.suc();
}
