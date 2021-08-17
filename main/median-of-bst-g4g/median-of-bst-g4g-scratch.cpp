#include<iostream>
using namespace std;
struct Node{
	int data;
	struct Node* left, *right;
};
struct Node *newNode(int item){
	struct Node *temp = new Node;
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}
struct Node* insert(struct Node* node, int key){
	if (node == NULL) return newNode(key);
	if (key < node->data)
		node->left = insert(node->left, key);
	else if (key > node->data)
		node->right = insert(node->right, key);
	return node;
}
float findMedian(struct Node *root,int n);
// Driver Program to test above functions
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        struct Node *root = NULL;
        int n, temp;
        cin>>n;
       for(int i=0;i<n;i++)
        {
            cin>>temp;
            root = insert(root, temp);
        }
        cout<<findMedian(root,n)<<'
';
    }
	return 0;
}

/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/*
Structure of the binary Search Tree is as
struct Node
{
	int key;
	struct Node *left, *right;
};
*/

#include <cassert>
#include <limits>
#include <stack>

namespace {
    constexpr auto k_debug_inorder = true;
}

// your task is to complete the Function
// Note: Function should return median of the BST
float findMedian(Node* const root, const int n)
{
    assert(n > 0);
    const auto half = n / 2;
    auto count = 0;
    auto midval = numeric_limits<long long>::min(); // can start as anything

    stack<const Node*> nodes;
    for (const auto* cur {root}; ; cur = cur->right) {
        for (; cur; cur = cur->left) nodes.push(cur); // traverse left

        assert(!nodes.empty());
        cur = nodes.top();
        nodes.pop();
        if (k_debug_inorder) cout << '(' << cur->data << ") ";

        if (++count >= half) {
            if (n % 2 != 0) {
                if (count != half) { // at exact middle
                    return static_cast<float>(cur->data);
                }
            }
            else if (count == half) {   // at left-mid element
                midval = cur->data;
            } else {                    // at right-mid element
                return static_cast<float>((midval + cur->data) / 2.0);
            }
        }
    }
}
