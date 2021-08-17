/* This function tests if a binary tree is perfect
   or not. It basically checks for two things :
   1) All leaves are at same level
   2) All internal nodes have two children */
bool isPerfectRec(struct Node* root, const int tree_depth,
                                     const int current_level)
{
    if (root == nullptr) return current_level == tree_depth;
    
    return isPerfectRec(root->left, tree_depth, current_level + 1)
            && isPerfectRec(root->right, tree_depth, current_level + 1);
}
