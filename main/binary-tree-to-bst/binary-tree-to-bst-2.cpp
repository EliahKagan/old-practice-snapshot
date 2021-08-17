#include "binary-tree-to-bst-2.h" //#include <bits/stdc++.h>
using namespace std;
/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};
void printInorder (struct Node* node)
{
    if (node == NULL)
        return;

    /* first recur on left child */
    printInorder (node->left);

    /* then print the data of node */
    printf("%d ", node->data);

    /* now recur on right child */
    printInorder (node->right);
}
Node *  binaryTreeToBST (Node *root);

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct Node* newNode(int data)
{
  struct Node* node = (struct Node*)
                       malloc(sizeof(struct Node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return(node);
}
/* Driver program to test size function*/
int main()
{
  int t;
  struct Node *child;
  scanf("%d", &t);
  while (t--)
  {
     map<int, Node*> m;
     int n;
     scanf("%d",&n);
     struct Node *root = NULL;
     while (n--)
     {
        Node *parent;
        char lr;
        int n1, n2;
        scanf("%d %d %c", &n1, &n2, &lr);
        if (m.find(n1) == m.end())
        {
           parent = newNode(n1);
           m[n1] = parent;
           if (root == NULL)
             root = parent;
        }
        else
           parent = m[n1];
        child = newNode(n2);
        if (lr == 'L')
          parent->left = child;
        else
          parent->right = child;
        m[n2]  = child;
     }
     Node *res = binaryTreeToBST (root);
     printInorder(res);
     cout<<endl;
    // cout << endl;
  }
  return 0;
}

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
