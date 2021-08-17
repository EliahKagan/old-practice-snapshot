/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
   struct Node {
      int data;
      Node* left;
      Node* right;
   }
*/

static bool checkBST(const Node* const root,
                     const int lower_bound, const int upper_bound)
{
    return root == nullptr
            || (lower_bound < root->data && root->data < upper_bound
                && checkBST(root->left, lower_bound, root->data)
                && checkBST(root->right, root->data, upper_bound));
}

bool checkBST(Node* root)
{
    return checkBST(root, -1, 10001);
}
