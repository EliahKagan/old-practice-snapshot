/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for C++
/*
Structure of the Node of the tree is
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};*/
// Your task is to complete this function
// function shoudl return the required sum
int minLeafSum(Node* root)
{
    auto sum = 0;
    if (!root) return sum;

    queue<const Node*> q;
    q.push(root);

    for (auto go_lower = true; go_lower; ) {
        for (auto width = q.size(); width != 0u; --width) {
            const auto node = q.front();
            q.pop();

            if (node->left || node->right) {
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            } else {
                sum += node->data;
                go_lower = false;
            }
        }
    }

    return sum;
}
