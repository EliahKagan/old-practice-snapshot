/*
Please note that it's Function problem i.e.
you need to write your solution in the form Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


// A recursive function to find depth of the deepest odd level leaf
int depthOfOddLeafUtil(struct Node *const root, const int level)
{
    if (root == nullptr) return 0;
    
    if (root->left == nullptr && root->right == nullptr)
        return level % 2 == 0 ? 0 : level;
    
    return max(depthOfOddLeafUtil(root->left, level + 1),
               depthOfOddLeafUtil(root->right, level + 1));
}
