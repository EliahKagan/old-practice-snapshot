/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    static int diameterOfBinaryTree(const TreeNode* root);
};

namespace {
    // This template is based on https://stackoverflow.com/a/40873657,
    // by https://stackoverflow.com/users/2069064/barry.
    template<typename F>
    class FixedPoint {
    public:
        explicit FixedPoint(const F& func) : func_{func} { }
        explicit FixedPoint(F&& func) : func_{std::move(func)} { }
        
        template<typename... Ts>
        decltype(auto) operator()(Ts&&... xs) const
        {
            return func_(std::cref(*this), std::forward<Ts>(xs)...);
        }
        
    private:
        F func_;
    };
    
    template<typename F>
    inline auto fixed_point(F&& func)
    {
        return FixedPoint<std::decay_t<F>>{std::forward<F>(func)};
    }
}

int Solution::diameterOfBinaryTree(const TreeNode* const root)
{
    auto diameter = 0;
    
    const auto dfs = fixed_point([&diameter](const auto dfs,
                                             const TreeNode* const node) {
        if (!node) return 0;

        const auto lh = dfs(node->left), rh = dfs(node->right);
        diameter = std::max(diameter, lh + rh);

        return 1 + std::max(lh, rh);
    });
    
    dfs(root);
    return diameter;
}
