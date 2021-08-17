/*
// Definition for a Node.
class Node {
public:
    int val;
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
    static int maxDepth(Node* root);
};

int Solution::maxDepth(Node* root)
{
    if (!root) return 0;

    queue<const Node*> q;
    q.push(root);
    auto depth = 0;

    while (!q.empty()) {
        ++depth;

        for (auto breadth = q.size(); breadth != 0u; --breadth) {
            const auto parent = q.front();
            q.pop();

            for (const auto child : parent->children)
                if (child) q.push(child);
        }
    }

    return depth;
}
