/*The Node structure is defined as
struct Node
{
    int key;
    Node *left, *right;
}; */

#include <cassert>
#include <functional>

/*Complete the function below*/
void kthLargest(Node *root, int k)
{
    assert(k > 0);
    
    // Recursive reverse (max to min) inorder order traversal.
    const function<int(Node *)> traverse {[&k, &traverse](Node *const p) {
        static constexpr auto not_done = -1;
        
        if (p == nullptr) return not_done;
        
        const auto right = traverse(p->right);
        if (right != not_done) return right;
        
        return --k == 0 ? p->key : traverse(p->left);
    }};
    
    cout << traverse(root) << '\n';
}
