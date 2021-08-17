/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/* The Node structure is
struct Node
{
    int data;
    Node* left;
    Node* right;
}; */

namespace {
    struct MetaNode {
        Node* node;
        unique_ptr<MetaNode> left, right;
    };

    unique_ptr<MetaNode> buildMetaTreeAndPopulateVector(Node* const root,
                                                        vector<Node*>& nodes)
    {
        if (!root) return nullptr;

        // We can populate the vector in any order. Inorder traversal lets us
        // convert to stable sort by changing std::sort to std::stable_sort.
        // Debugging by inspecting the (unsorted) vector is also made easy.
        auto metaLeft = buildMetaTreeAndPopulateVector(root->left, nodes);
        nodes.push_back(root);
        auto metaRight = buildMetaTreeAndPopulateVector(root->right, nodes);

        return unique_ptr<MetaNode>{new MetaNode{nullptr, move(metaLeft),
                                                          move(metaRight)}};
    }

    void sortByData(vector<Node*>& nodes) noexcept
    {
        sort(begin(nodes), end(nodes), [](const Node* const lhs,
                                          const Node* const rhs) noexcept {
            return lhs->data < rhs->data;
        });
    }

    void populateMetaTree(const unique_ptr<MetaNode>& metaRoot,
                          vector<Node*>::const_iterator& it) noexcept
    {
        if (!metaRoot) return;

        // We MUST populate via inorder traversal.
        populateMetaTree(metaRoot->left, it);
        metaRoot->node = *it;
        ++it;
        populateMetaTree(metaRoot->right, it);
    }

    Node* reassembleTree(unique_ptr<MetaNode>&& metaRoot) noexcept
    {
        if (!metaRoot) return nullptr;

        // We can reassemble in any order, and preorder traversal is simple.
        const auto node = metaRoot->node;
        node->left = reassembleTree(move(metaRoot->left));
        node->right = reassembleTree(move(metaRoot->right));
        metaRoot = nullptr;

        return node;
    }
}

Node* binaryTreeToBST(Node* root)
{
    vector<Node*> nodes;
    auto metaRoot = buildMetaTreeAndPopulateVector(root, nodes);
    sortByData(nodes);

    auto it = nodes.cbegin();
    populateMetaTree(metaRoot, it);
    assert(it == nodes.cend());

    return reassembleTree(move(metaRoot));
}
