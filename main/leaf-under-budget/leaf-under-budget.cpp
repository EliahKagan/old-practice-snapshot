/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*
Structure of the node of the binary tree is as
struct node
{
    int data;
    struct node* left;
    struct node* right;
};
*/
// your are required to complete this function
// function should return the number of leaf node
// one can visit
int getCount(struct node* root, int budget)
{
    auto count = 0;
    if (!root) return count;

    auto cost = 1;

    queue<const struct node*> q;
    q.push(root);

    while (!q.empty()) {
        for (auto width = q.size(); width != 0u; --width) {
            if (cost > budget) return count;

            const auto cur = q.front();
            q.pop();

            if (cur->left || cur->right) {
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            } else {
                ++count;
                budget -= cost;
            }
        }

        ++cost;
    }

    return count;
}
