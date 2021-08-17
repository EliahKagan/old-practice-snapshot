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
bool ifCousin(Node *const root, Node *const a, Node *const b)
{
    if (!root || !a || !b) return false;

    const auto aval = a->data, bval = b->data;

    queue<const Node*> q;
    q.push(root);

    while (!q.empty()) {
        auto afound = false, bfound = false;

        for (auto width = q.size(); width != 0u; --width) {
            const auto parent = q.front();
            q.pop();

            auto ahere = false, bhere = false;

            for (const auto child : {parent->left, parent->right}) {
                if (!child) continue;

                if (child->data == aval) {
                    if (bfound) return true;
                    ahere = true;
                }

                if (child->data == bval) {
                    if (afound) return true;
                    bhere = true;
                }

                q.push(child);
            }

            afound |= ahere;
            bfound |= bhere;
        }
    }

    return false;
}
