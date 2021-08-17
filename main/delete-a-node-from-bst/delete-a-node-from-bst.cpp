/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/* The structure of a BST Node is as follows:
struct Node {
  int data;
  Node * right, * left;
}; */

namespace {
    Node*& find(Node*& root, const int key)
    {
        if (!root || root->data == key) return root;

        for (auto parent = root; ; ) {
            auto& child = (key < parent->data ? parent->left : parent->right);
            if (!child || child->data == key) return child;
            parent = child;
        }
    }

    Node*& findMin(Node*& root)
    {
        assert(root);
        if (!root->left) return root;

        auto parent = root;
        while (parent->left->left) parent = parent->left;
        return parent->left;
    }

    Node* extractMin(Node*& root)
    {
        auto& pos = findMin(root);
        auto ret = pos;
        pos = ret->right;
        return ret;
    }

    void replace(Node*& pos, Node* node)
    {
        node->left = pos->left;
        node->right = pos->right;
        pos = node;
    }
}

Node* deleteNode(Node* root, const int key)
{
    auto& pos = find(root, key);

    if (pos) {
        if (!pos->left)
            pos = pos->right;
        else if (!pos->right)
            pos = pos->left;
        else
            replace(pos, extractMin(pos->right));
    }

    return root;
}
