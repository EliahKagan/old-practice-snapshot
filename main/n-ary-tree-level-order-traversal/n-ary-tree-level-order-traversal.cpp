/*
// Definition for a Node.
class Node {
public:
    int val = NULL;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
public:
    static vector<vector<int>> levelOrder(const Node* root);
};

vector<vector<int>> Solution::levelOrder(const Node* const root)
{
    vector<vector<int>> table;
    if (!root) return table;

    queue<const Node*> q;
    q.push(root);

    while (!q.empty()) {
        vector<int> row;

        for (auto breadth = q.size(); breadth != 0u; --breadth) {
            const auto parent = q.front();
            q.pop();

            row.push_back(parent->val);

            for (const auto child : parent->children)
                if (child) q.push(child);
        }

        table.push_back(move(row));
    }

    return table;
}