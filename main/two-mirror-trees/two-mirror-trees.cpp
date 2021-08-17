/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/* Node structure
struct Node
{
    int data;
    Node* left, *right;
}; */
/* Given two trees, should return true if they are
   mirror of each other. */
int areMirror(Node* a, Node* b)
{
    if (!a || !b) return a == b;

    return a->data == b->data && areMirror(a->left, b->right)
                              && areMirror(a->right, b->left);
}
