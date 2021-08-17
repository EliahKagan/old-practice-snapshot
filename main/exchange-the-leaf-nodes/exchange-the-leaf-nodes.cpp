/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for C++
/*
struct Node
{
	int data;
	struct Node *left, *right;
};
*/

// your task is to complete this function
void pairwiseSwap(Node* root)
{
    Node** leafpp = nullptr;

    const function<void(Node*&)> dfs {[&leafpp, &dfs](Node*& node) {
        if (node == nullptr) return;

        if (node->left != nullptr || node->right != nullptr) {
            dfs(node->left);
            dfs(node->right);
        }
        else if (leafpp != nullptr) {
            swap(*leafpp, node);
            leafpp = nullptr;
        }
        else leafpp = &node;
    }};

    dfs(root);
}
