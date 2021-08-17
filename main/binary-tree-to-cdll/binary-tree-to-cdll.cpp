
namespace {
    vector<Node *> inOrder(Node *const root)
    {
        vector<Node *> a;

        const function<void(Node *)> dfs {[&dfs, &a](Node *const cur) {
            if (cur != nullptr) {
                dfs(cur->left);
                a.push_back(cur);
                dfs(cur->right);
            }
        }};

        dfs(root);
        return a;
    }

    inline void link(Node *const left, Node *const right)
    {
        left->right = right;
        right->left = left;
    }
}

/*Complete the function below
Node is as follows:
struct Node
{
    struct Node *left, *right;
    int data;
};*/

Node *bTreeToCList(Node *const root)
{
    if (root == nullptr) return nullptr;

    const auto a = inOrder(root);

    const auto qq = a.cend();
    for (auto p = a.cbegin(), q = next(p); q != qq; ++p, ++q) link(*p, *q);
    link(a.back(), a.front());

    return a.front();
}
