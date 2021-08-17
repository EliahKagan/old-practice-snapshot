/*Complete the function below
Node is as follows
struct Node{
	int data;
	Node *left, *right;
};
*/
int maxPathSum(Node *const root)
{
    if (root == nullptr) return 0;

    auto acc = numeric_limits<int>::min();

    const function<int(const Node *)> // puts max leaf-to-leaf sum in acc
    maxSumToLeaf {[&maxSumToLeaf, &acc](const Node* const cur) {
        if (cur->left == nullptr && cur->right == nullptr) return cur->data;

        if (cur->left == nullptr) return cur->data + maxSumToLeaf(cur->right);
        if (cur->right == nullptr) return cur->data + maxSumToLeaf(cur->left);

        const auto left_sum = maxSumToLeaf(cur->left);
        const auto right_sum = maxSumToLeaf(cur->right);

        acc = max(acc, cur->data + left_sum + right_sum);
        return cur->data + max(left_sum, right_sum);
    }};

    maxSumToLeaf(root);
    return acc;
}
