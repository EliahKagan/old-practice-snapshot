/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for C++
/*Structure of the node of the binary tree is as
struct Node {
	int data;
	struct Node *left, *right;
};
*/
// your task is to complete this function
// Function takes a single argument as input
// the root of the binary tree
// print a new line after each test case
void zigZagTraversal(Node* const root)
{
    if (root == nullptr) return;

    deque<const Node*> q;
    for (q.push_front(root); !q.empty(); ) {
        for (auto width = q.size(); width != 0u; --width) {
            const auto node = q.front();
            q.pop_front();

            cout << node->data << ' ';
            if (node->left != nullptr) q.push_back(node->left);
            if (node->right != nullptr) q.push_back(node->right);
        }

        for (auto width = q.size(); width != 0u; --width) {
            const auto node = q.back();
            q.pop_back();

            cout << node->data << ' ';
            if (node->right != nullptr) q.push_front(node->right);
            if (node->left != nullptr) q.push_front(node->left);
        }
    }

    cout << '\n';
}
