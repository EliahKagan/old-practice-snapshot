/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for C++
/*
structure of the node of the binary tree is as
struct Node {
	int data;
	Node* left, *right;
};
*/

namespace {
    enum { length, sum };

    tuple<int, int> lengthAndSumOfLongRootToLeafPath(const Node* const root)
    {
        if (root == nullptr) return make_tuple(0, 0);

        auto ret = max(lengthAndSumOfLongRootToLeafPath(root->left),
                       lengthAndSumOfLongRootToLeafPath(root->right));

        ++get<length>(ret);
        get<sum>(ret) += root->data;

        return ret;
    }
}

// your task is to complete this function
int sumOfLongRootToLeafPath(Node* const root)
{
    return get<sum>(lengthAndSumOfLongRootToLeafPath(root));
}
