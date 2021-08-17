/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct IndexedNode {
    int index;
    const TreeNode* node;

    IndexedNode(int index, const TreeNode* node)
        : index{index}, node{node} { }

    operator tuple<int&, const TreeNode*&>() {
        return tie(index, node);
    }
};

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        auto acc = 0;
        if (root == nullptr) return acc;

        vector<IndexedNode> this_row {IndexedNode{1, root}};
        vector<IndexedNode> next_row;

        while (!this_row.empty()) {
            acc = max(acc, this_row.back().index - this_row.front().index + 1);

            int index {};
            const TreeNode* node {};

            for (auto p = begin(this_row); p != end(this_row); ++p) {
                tie(index, node) = *p;

                if (node->left != nullptr) {
                    next_row.push_back(IndexedNode{index * 2,
                                                   node->left});
                }
                if (node->right != nullptr) {
                    next_row.push_back(IndexedNode{index * 2 + 1,
                                                   node->right});
                }
            }

            swap(this_row, next_row);
            next_row.clear();

        }

        return acc;
    }
};
