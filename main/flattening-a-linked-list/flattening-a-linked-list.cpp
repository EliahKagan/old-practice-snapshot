/* Node structure  used in the program
struct Node{
	int data;
	struct Node * next;
	struct Node * bottom ;
}; */

namespace {
    void dfs_flatten(vector<Node *>& dest, Node *const root)
    {
        if (root != nullptr) {
            dest.push_back(root);
            dfs_flatten(dest, root->bottom);
            dfs_flatten(dest, root->next);
        }
    }
}

/*  Function which returns the  root of 
    the flattened linked list. */
Node *flatten(Node *const root)
{
    if (root == nullptr) return nullptr;
    
    vector<Node *> a;
    dfs_flatten(a, root);
    
    sort(a.begin(), a.end(), [](Node *const lhs, Node *const rhs) {
        return lhs->data < rhs->data;
    });
    
    const auto qq = a.cend();
    for (auto p = a.cbegin(), q = next(p); q != qq; ++p, ++q) {
        (*p)->next = nullptr;
        (*p)->bottom = *q;
    }
    
    a.back()->bottom = a.back()->next = nullptr;
    return a.front();
}
