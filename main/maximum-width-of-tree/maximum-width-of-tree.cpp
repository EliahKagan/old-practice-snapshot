/*  Structure of a Binary Tree
struct Node
{
    int data;
    Node* left, *right;
}; */

/* Function to get the maximum width of a binary tree*/
int getMaxWidth(Node* root)
{
    if (root == nullptr) return 0;

    std::queue<Node*>::size_type max_width {0u};

    queue<Node*> q;
    for (q.push(root); !q.empty(); ) {
        auto width = q.size();
        for (max_width = max(max_width, width); width != 0u; --width) {
            root = q.front();
            q.pop();

            if (root->left != nullptr) q.push(root->left);
            if (root->right != nullptr) q.push(root->right);
        }
    }

    return static_cast<int>(max_width);
}
