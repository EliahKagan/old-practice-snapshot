/*
struct node
{
    int data;
    node* left;
    node* right;
};

*/

void left_view(node* root) // low to high
{
    if (root == nullptr) return;
    left_view(root->left);
    std::cout << root->data << ' ';
}

void right_view(node* root) // high to low
{
    if (root == nullptr) return;
    std::cout << root->data << ' ';
    right_view(root->right);
}

void top_view(node* root)
{
    if (root == nullptr) return;
    left_view(root->left);
    std::cout << root->data << ' ';
    right_view(root->right);
}
