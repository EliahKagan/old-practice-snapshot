/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for C++
/*
Structure of the node of the binary tree is as
struct Node
{
	int data;
	struct Node *left, *right;
};
*/

namespace {
    const Node failure_sentinel {};
    const auto failure_data = -1;

    const Node* kthAncestorNode(vector<const Node*>& ancestry,
            const size_t generation, const int key, const Node* const subroot)
    {
        if (subroot) {
            ancestry.push_back(subroot);

            if (subroot->data == key) {
                const auto depth = ancestry.size();

                return generation < depth ? ancestry[depth - 1u - generation]
                                          : &failure_sentinel;
            } else {
                const auto left_result = kthAncestorNode(ancestry, generation,
                                                         key, subroot->left);
                if (left_result) return left_result;

                const auto right_result = kthAncestorNode(ancestry, generation,
                                                          key, subroot->right);
                if (right_result) return right_result;
            }

            ancestry.pop_back();
        }

        return nullptr;
    }
}

// your task is to complete this function
int kthAncestor(Node* const root, const int generation, const int key)
{
    if (generation <= 0) return -1;

    vector<const Node*> ancestry;

    const auto result = kthAncestorNode(ancestry,
                                        static_cast<size_t>(generation),
                                        key,
                                        root);

    return !result || result == &failure_sentinel ? failure_data
                                                  : result->data;
}
