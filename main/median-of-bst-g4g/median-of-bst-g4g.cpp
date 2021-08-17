/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/*
Structure of the binary Search Tree is as
struct Node
{
	int key;
	struct Node *left, *right;
};
*/

#include <cassert>
#include <stack>
#include <vector>

namespace {
    vector<int> inorder(const Node* root)
    {
        static constexpr auto debug_traversal = false;
        vector<int> a;

        for (stack<const Node*> s; root || !s.empty(); root = root->right) {
            for (; root; root = root->left) s.push(root); // traverse right

            root = s.top();
            s.pop();
            a.push_back(root->data);
        }

        if (debug_traversal) {
            cout << '[';
            for (const auto e : a) cout << ' ' << e;
            cout << " ]\n";
        }

        return a;
    }
}

// your task is to complete the Function
// Note: Function should return median of the BST
float findMedian(Node* const root, int)
{
    const auto a = inorder(root);
    assert(!a.empty());

    const auto len = a.size(), mid = len / 2u;

    if (len % 2u != 0u) return static_cast<float>(a[mid]);

    // doing it this way to make overflow occur for fewer possible values
    const auto lowval = static_cast<double>(a[mid - 1]);
    const auto highval = static_cast<double>(a[mid]);
    return static_cast<float>((lowval + highval) / 2.0);
}
