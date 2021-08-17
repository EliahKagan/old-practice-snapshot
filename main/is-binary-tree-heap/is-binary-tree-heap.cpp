/*
 A binary tree node has data, pointer to left child
   and a pointer to right child 
struct Node
{
    int data;
    Node* left;
    Node* right;
};
*/

namespace {
    bool isSubHeap(const Node* const tree, const int bound)
    {
        return tree->data <= bound
                && (!tree->left || isSubHeap(tree->left, tree->data))
                && (!tree->right || isSubHeap(tree->right, tree->data));
    }
}

/*You are required to complete this method */
bool isHeap(Node* tree)
{
    return !tree || isSubHeap(tree, numeric_limits<int>::max());
}
