/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*Complete the function below
Node is as follows:
struct Node{
  ll data;
  Node *left,*right;
};
*/
bool ifCousin(Node* const root, Node* const a, Node* const b)
{
    if (!root || !a || !b || root == a || root == b || a == b) return false;

    queue<const Node*> q;
    q.push(root);

    while (!q.empty()) {
        auto found_one = false;

        for (auto width = q.size(); width != 0u; --width) {
            const auto cur = q.front();
            q.pop();

            const auto is_left = cur->left == a || cur->left == b;
            const auto is_right = cur->right == a || cur->right == b;

            if (is_left || is_right) {
                if (is_left && is_right) return false; // siblings
                if (found_one) return true; // cousins
                found_one = true;
            }

            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }

        if (found_one) return false; // a simple optimization
    }

    return false;
}
