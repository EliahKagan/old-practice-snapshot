/* A binary tree node
struct Node
{
    int data;
    Node* left, * right;
}; */

namespace {
    bool dfs(Node* const root, const int key, vector<Node*>& path)
    {
        if (root != nullptr) {
            path.push_back(root);
            
            if (root->data == key || dfs(root->left, key, path)
                                  || dfs(root->right, key, path))
                return true;
            
            path.pop_back();
        }
        
        return false;
    }
    
    vector<Node*> dfs(Node* const root, const int key)
    {
        vector<Node*> path;
        dfs(root, key, path);
        return path;
    }
}

Node* LCA(Node* root, const int n1, const int n2)
{
    const auto a = dfs(root, n1), b = dfs(root, n2);
    
    Node* ret {};
    
    const auto pp = a.cend(), qq = b.cend();
    for (auto p = a.cbegin(), q = b.cbegin(); p != pp && q != qq; ++p, ++q)
        if (*p == *q) ret = *p;
    
    return ret;
}
