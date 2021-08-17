
namespace {
    int longestConsecutive(const Node* parent, int parent_depth);

    int longestConsecutive(const Node* const parent, const Node* const child,
                           const int parent_depth)
    {
        if (child == nullptr) return parent_depth;

        if (child->data - parent->data == 1)
            return longestConsecutive(child, parent_depth + 1);

        return max(parent_depth, longestConsecutive(child, 1));
    }

    int longestConsecutive(const Node* const parent, const int parent_depth)
    {
        return max(longestConsecutive(parent, parent->left, parent_depth),
                   longestConsecutive(parent, parent->right, parent_depth));
    }
}

/*
struct Node
{
	int data;
	Node *left, *right;
};
*/
// your task is tp complete this function
// function should return the length of the longestConsecutive
// sequence
int longestConsecutive(Node* const root)
{
    if (root == nullptr) return 0;
    const auto depth = longestConsecutive(root, 1);
    return depth == 1 ? -1 : depth;
}
