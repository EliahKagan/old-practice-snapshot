/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for C++
/*
Structure of the Node of the BST is as
struct Node {
	int key;
	Node* left, *right;
};
*/
int findMaxforN(Node* root, const int n)
{
    auto best = -1;

    while (root != nullptr) {
        assert(root->key >= 0);

        if (root->key > n) {
            root = root->left;
        } else {
            best = root->key;
            if (best == n) break;
            root = root->right;
        }
    }

    return best;
}
