#include "nodes-at-given-distance-in-binary-tree.h" //#include<bits/stdc++.h>
using namespace std;
// A binary Tree node
struct node
{
    int data;
    struct node *left, *right;
};
int counter = 0;
int target = 0;
struct node *ptr = NULL;
void printkdistanceNodeDown(node *root, int k);
int printkdistanceNode(node* root, node* target, int k);

// A utility function to create a new binary tree node
node *newnode(int data)
{
    node *temp = new node;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}
void insert(struct node *root, int n1, int n2, char lr)
{
    if (root == NULL)
        return;
    if (root->data == n1)
    {
        switch (lr)
        {
        case 'L': root->left = newnode(n2);
            break;
        case 'R': root->right = newnode(n2);
            break;
        }
    }
    else
    {
        insert(root->left, n1, n2, lr);
        insert(root->right, n1, n2, lr);
    }
}
void Inorder(struct node* root)
{

    if (counter == 0)
    {
        cin >> target;
        counter++;
    }

    if (root == NULL)
        return;

    Inorder(root->left);

    if (root->data == target)
        ptr = root;

    Inorder(root->right);
}
// Driver program to test above functions
int main()
{
    /* Let us construct the tree shown in above diagram */
    int t, k;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        struct node *root = NULL;
        while (n--)
        {
            char lr;
            int n1, n2;
            cin >> n1 >> n2;
            cin >> lr;
            if (root == NULL)
            {
                root = newnode(n1);
                switch (lr) {
                case 'L': root->left = newnode(n2);
                    break;
                case 'R': root->right = newnode(n2);
                    break;
                }
            }
            else
            {
                insert(root, n1, n2, lr);
            }
        }
        Inorder(root);
        node * target = ptr;
        cin >> k;
        printkdistanceNode(root, target, k);
        cout << endl;
        counter = 0;
    }
    return 0;
}

/* A binary Tree node
struct node
{
    int data;
    struct node *left, *right;
}; */

namespace {
    constexpr auto debugDfs = false;

    enum class NextAction { // next step in "recursive" DFS
        checkNullCheckMatchVisitLeftSubtree,
        visitRightSubtree,
        popAndReturn
    };

    inline void print(const NextAction action) // for debugging DFS
    {
        switch (action) {
        case NextAction::checkNullCheckMatchVisitLeftSubtree:
            cout << "checkNullCheckMatchVisitLeftSubtree ";
            return;

        case NextAction::visitRightSubtree:
            cout << "visitRightSubtree ";
            return;

        case NextAction::popAndReturn:
            cout << "popAndReturn ";
            return;
        }

        throw invalid_argument{"value out of range of NextAction enumeration"};
    }

    inline void print(const node* const p) // for output (and debugging DFS)
    {
        if (debugDfs && p == nullptr) cout << "null ";
        else cout << p->data << ' ';
    }

    template<typename T>
    void print(const char* const name, stack<T>& items) // for debugging DFS
    {
        cout << "DEBUG: " << name << ": [ ";

        stack<T> aux;
        for (; !items.empty(); items.pop()) aux.push(items.top());

        for (; !aux.empty(); aux.pop()) {
            items.push(aux.top());
            print(items.top());
        }

        cout << "]\n";
    }

    inline void checkForCorruption(stack<NextAction>& actions,
                                   stack<node*>& path)
    {
        if (debugDfs) {
            print("actions", actions);
            print("   path", path);
        }

        assert(actions.size() == path.size());
    }

    inline bool checkNullCheckMatchVisitLeftSubtree(
            stack<NextAction>& actions, stack<node*>& path, node *const target)
    {
        if (path.top() == nullptr) actions.top() = NextAction::popAndReturn;
        else if (path.top() == target) return false; // done
        else {
            actions.top() = NextAction::visitRightSubtree;
            actions.push(NextAction::checkNullCheckMatchVisitLeftSubtree);
            path.push(path.top()->left);
        }

        return true;
    }

    inline bool visitRightSubtree(stack<NextAction>& actions,
                                  stack<node*>& path)
    {
        actions.top() = NextAction::popAndReturn;
        actions.push(NextAction::checkNullCheckMatchVisitLeftSubtree);
        path.push(path.top()->right);
        return true;
    }

    inline bool popAndReturn(stack<NextAction>& actions, stack<node*>& path)
    {
        actions.pop();
        path.pop();
        return !path.empty(); // done if the stack is empty
    }

    // Advances the state of the depth-first search.
    // Returns false when done (target found or absent), and true otherwise.
    inline bool advance(stack<NextAction>& actions, stack<node*>& path,
                        node* const target)
    {
        checkForCorruption(actions, path);

        switch (actions.top()) {
        case NextAction::checkNullCheckMatchVisitLeftSubtree:
            return checkNullCheckMatchVisitLeftSubtree(actions, path, target);

        case NextAction::visitRightSubtree:
            return visitRightSubtree(actions, path);

        case NextAction::popAndReturn:
            return popAndReturn(actions, path);
        }

        throw invalid_argument{"value out of range of NextAction enumeration"};
    }

    stack<node*> dfs(node* const root, node* const target)
    {
        stack<NextAction> actions;
        actions.push(NextAction::checkNullCheckMatchVisitLeftSubtree);

        stack<node*> path;
        path.push(root);

        while (advance(actions, path, target)) { }
        return path;
    }

    inline node* getSibling(node* const parent, node* const child)
    {
        if (parent->left == child) return parent->right;
        else if (parent->right == child) return parent->left;
        else throw invalid_argument{"no parent-child relationship"};
    }

    int printFromEachAncestor(stack<node*>& path, int k) // returns final k
    {
        while (!path.empty()) {
            const auto prev = path.top();
            path.pop();

            if (--k == 0 || path.empty()) break;
            printkdistanceNodeDown(getSibling(path.top(), prev), k - 1);
        }

        return k;
    }

    void printkdistanceNodeFromPath(stack<node*>& path, const int k)
    {
        printkdistanceNodeDown(path.top(), k);

        if (printFromEachAncestor(path, k) == 0 && !path.empty())
            print(path.top());
    }
}

/* Recursive function to print all the nodes at distance k in the
   tree (or subtree) rooted with given root. See  */
void printkdistanceNodeDown(node* const root, const int k)
{
    assert(k >= 0);

    if (root != nullptr) {
        if (k > 0) {
            printkdistanceNodeDown(root->left, k - 1);
            printkdistanceNodeDown(root->right, k - 1);
        }
        else print(root);
    }
}

/* Prints all nodes at distance k from a given target node.
 The k distant nodes may be upward or downward.  This function
 Returns distance of root from target node, it returns -1 if target
 node is not present in tree rooted with root. */
int printkdistanceNode(node* const root, node* const target, const int k)
{
    assert(k >= 0);

    auto path = dfs(root, target);
    const auto depth = static_cast<int>(path.size()) - 1;
    
    if (depth != -1) {
        assert(path.top() == target);

        if (k == 0) print(target);
        else printkdistanceNodeFromPath(path, k);
    }

    return depth;
}
