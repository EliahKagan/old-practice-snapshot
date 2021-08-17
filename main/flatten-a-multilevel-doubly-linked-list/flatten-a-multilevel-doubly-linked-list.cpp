/*
// Definition for a Node.
class Node {
public:
    int val = NULL;
    Node* prev = NULL;
    Node* next = NULL;
    Node* child = NULL;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};
*/
class Solution {
public:
    static Node* flatten(Node* head);
};

namespace {
    template<typename F>
    void preorder_nodes(Node* root, F f)
    {
        stack<Node*> s;
        s.push(root);

        while (!s.empty()) {
            root = s.top();
            s.pop();
            if (!root) continue;

            s.push(root->next);
            s.push(root->child);
            f(root);
        }
    }
}

Node* Solution::flatten(Node* const head)
{
    Node sentinel {};
    auto pre = &sentinel;

    preorder_nodes(head, [&pre](Node* const cur) {
        pre->next = cur;
        cur->prev = pre;
        cur->child = nullptr;
        pre = cur;
    });

    pre->next = nullptr;
    if (sentinel.next) sentinel.next->prev = nullptr;
    return sentinel.next;
}
