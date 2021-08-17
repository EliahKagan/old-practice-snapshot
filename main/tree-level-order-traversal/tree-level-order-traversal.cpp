/*
struct node
{
    int data;
    node* left;
    node* right;
}*/

#include <queue>

void LevelOrder(node* const root)
{
    if (root == nullptr) return;
    std::queue<node*> q;
    q.push(root);
    
    do {
        const auto n = q.front();
        q.pop();
        std::cout << n->data << ' ';
        
        if (n->left != nullptr) q.push(n->left);
        if (n->right != nullptr) q.push(n->right);
    }
    while (!q.empty());
}
