/*Complete the function below
Node is as follows
struct node
{
    int val;
    struct node *left, *right;
};
*/
bool isPairPresent(struct node *const root, const int target)
{
    unordered_set<int> complements;

    const function<bool(const struct node *)>
    dfs {[&dfs, &complements, target](const struct node *const cur) {
        if (cur == nullptr) return false;

        if (complements.find(cur->val) != complements.end()) return true;

        complements.insert(target - cur->val);
        return dfs(cur->left) || dfs(cur->right);
    }};

    return dfs(root);
}
