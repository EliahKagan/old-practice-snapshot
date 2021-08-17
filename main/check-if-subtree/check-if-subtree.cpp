/* A binary tree node
struct Node
{
    int key;
    Node* left, * right;
}; */

#include <queue>

namespace {
    // Helper function for isSubtree().
    bool isEqualTree(const Node* const lhs, const Node* const rhs)
    {
        return lhs == nullptr ? rhs == nullptr
                              : rhs != nullptr && lhs->key == rhs->key
                                    && isEqualTree(lhs->left, rhs->left)
                                    && isEqualTree(lhs->right, rhs->right);
    }
}

// Checks if the tree rooted at pattern is a subtree of the tree rooted at
// tree. Uses the naive algorithm, attempting to match each subtree (rooted at
// a node in tree) with pattern. Does _not_ perform the obvious optimizations
// of (a) handling the empty case separately and not enqueuing, dequeueing,
// and checking trees "rooted" at null pointers or (b) not matching pattern
// against subtrees of tree rooted at child nodes of nodes where matches
// failed due to bottoming out. Although I expect this to be slower, at least
// for some trees, it is simple and fast enough, especially for the very small
// trees specified in the problem constraints.
bool isSubtree(Node* tree, Node* pattern)
{
    queue<Node*> q;
    for (q.push(tree); !q.empty(); ) {
        tree = q.front();
        q.pop();
        
        if (isEqualTree(tree, pattern)) return true;
        
        if (tree != nullptr) {
            q.push(tree->left);
            q.push(tree->right);
        }
    }
    
    return false;
}
