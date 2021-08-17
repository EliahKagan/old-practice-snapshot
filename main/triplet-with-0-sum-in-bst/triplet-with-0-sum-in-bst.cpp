/*Complete the function below
Node is as follows:
struct node
{
    int key;
    struct node *left;
    struct node *right;
};
*/

namespace {
    void inorder(vector<int>& dest, const node *const root)
    {
        if (root != nullptr) {
            inorder(dest, root->left);
            dest.push_back(root->key);
            inorder(dest, root->right);
        }
    }
}

bool isTripletPresent(node *root)
{
    vector<int> a;
    inorder(a, root);
    if (a.size() < 3u) return false;
    
    // Simple O(N^3) brute force algorithm should be sufficient (N <= 100).
    // This does not take advantage of the property that a is sorted.
    
    const auto rr = a.cend(), qq = prev(rr), pp = prev(qq);
    
    for (auto p = a.cbegin(); p != pp; ++p) {
        for (auto q = next(p); q != qq; ++q) {
            const auto key = -(*p + *q);
            
            for (auto r = next(q); r != rr; ++r)
                if (*r == key) return true;
        }
    }
    
    return false;
}
