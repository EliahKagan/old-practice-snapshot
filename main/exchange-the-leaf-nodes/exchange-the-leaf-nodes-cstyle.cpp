/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for C++
/*
struct Node
{
	int data;
	struct Node *left, *right;
};
*/

static void pairwiseSwapDfs(struct Node **rootp,
                            struct Node ***const leafpp)
{
    if (*rootp == NULL) return;

    if ((*rootp)->left != NULL || (*rootp)->right != NULL) {
        pairwiseSwapDfs(&(*rootp)->left, leafpp);
        pairwiseSwapDfs(&(*rootp)->right, leafpp);
    }
    else if (*leafpp != NULL) {
        struct Node *const leaf = **leafpp;
        **leafpp = *rootp;
        *rootp = leaf;

        *leafpp = NULL;
    }
    else *leafpp = rootp;
}

// your task is to complete this function
void pairwiseSwap(struct Node *root)
{
    struct Node **leafp = NULL;
    pairwiseSwapDfs(&root, &leafp);
}
