/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*Structure of the node of the binary tree is as
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};
*/
// your task is to complete the function
void printOddNodes(Node *root)
{
    if (root) {
        queue<const Node*> q;
        q.push(root);

        while (!q.empty()) {
            for (auto width = q.size(); width != 0u; --width) {
                const auto cur = q.front();
                q.pop();

                cout << cur->data << ' ';

                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }

            for (auto width = q.size(); width != 0u; --width) {
                const auto cur = q.front();
                q.pop();

                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
        }
    }

    cout << '\n';
}
