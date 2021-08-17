/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for C++
/*
Structure of the node of the binary tree is as
struct Node {
	int data;
	struct Node *left, *right;
};
*/
// your are required to complete this function
// function should return the count of the number of
// subtrees with Sum equal to X
int countSubtreesWithSumX(Node* const root, const int x)
{
    auto count = 0;

    const function<int(const Node*)>
    sum {[x, &count, &sum](const Node* const node) {
        if (node == nullptr) return 0;

        const auto ret = node->data + sum(node->left) + sum(node->right);
        if (ret == x) ++count;
        return ret;
    }};

    sum(root);
    return count;
}
