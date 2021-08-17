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

namespace {
    struct Frame {
        Frame(const Node* const node)
            : first{cbegin(node->children)}, last{cend(node->children)},
              val{node->val} { }
        
        vector<Node*>::const_iterator first;
        vector<Node*>::const_iterator last;
        int val;
    };
}

vector<int> Solution::postorder(const Node* root)
{
    vector<int> ret;
    stack<Frame> s;
    if (root) s.emplace(root);
    
    while (!s.empty()) {
        auto& frame = s.top();
        
        if (frame.first == frame.last) {
            ret.push_back(frame.val);
            s.pop();
        } else {
            s.emplace(*frame.first);
            ++frame.first;
        }
    }
    
    return ret;
}
