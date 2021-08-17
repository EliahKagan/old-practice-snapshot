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
        const auto node = pos;

        if (!node->left)
            pos = node->right;
        else if (!node->right)
            pos = node->left;
        else
            replace(pos, extractMin(node->right));

        free(node);
    }

    return root;
}
