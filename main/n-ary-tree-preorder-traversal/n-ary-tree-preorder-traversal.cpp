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
    static vector<int> preorder(const Node* root);
};

vector<int> Solution::preorder(const Node* const root)
{
    vector<int> ret;
    
    stack<const Node*> s;
    s.push(root);
    
    while (!s.empty()) {
        const auto parent = s.top();
        s.pop();
        if (!parent) continue;
        
        ret.push_back(parent->val);
        
        for_each(crbegin(parent->children), crend(parent->children),
                 [&s](const auto child) { s.push(child); });
    }
    
    return ret;
}
