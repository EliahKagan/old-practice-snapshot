/*The structure of node is as follows
struct node{
	string data;
	node *left;
	node *right;
};
*/

/*You are required to complete below method */
int evalTree(node* const root)
{
    if (root->left == nullptr || root->right == nullptr) {
        istringstream in {root->data};
        int value {};
        in >> value;
        return value;
    }
    
    const auto x = evalTree(root->left), y = evalTree(root->right);
    if (root->data == "+") return x + y;
    if (root->data == "-") return x - y;
    if (root->data == "*") return x * y;
    if (root->data == "/") return x / y;
    throw std::invalid_argument{"unrecognized binary operator"};
}
