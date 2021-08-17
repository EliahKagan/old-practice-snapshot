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
    static vector<int> postorder(const Node* root);
};

vector<int> Solution::postorder(const Node* const root)
{
    vector<int> ret;
    
    stack<const Node*> s;
    s.push(root);
    
    while (!s.empty()) {
        const auto parent = s.top();
        s.pop();
        if (!parent) continue;
        
        ret.push_back(parent->val);
        for (const auto child : parent->children) s.push(child);
    }
    
    reverse(begin(ret), end(ret));
    return ret;
}
