/*
The structure of Link list node is as follows 
struct node
{
    int data;
    struct node* next;
};

The structure of TreeNode is as follows
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
};
*/

/*You are required to complete this method*/
void convert(node *head, TreeNode *&root)
{
    root = nullptr;
    
    queue<TreeNode **> leaf_ptrs;
    for (leaf_ptrs.push(&root); head != nullptr; head = head->next) {
        const auto p = leaf_ptrs.front();
        leaf_ptrs.pop();
        
        *p = new TreeNode{head->data, nullptr, nullptr};
        
        leaf_ptrs.push(&(*p)->left);
        leaf_ptrs.push(&(*p)->right);
    }
}
