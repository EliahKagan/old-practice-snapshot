/*Node structure
struct Node
{
	int data;
	struct Node *left, *right;
};*/

namespace {
    void appendToVector(const Node* const root, vector<int>& acc)
    {
        if (root != nullptr) {
            appendToVector(root->left, acc);
            acc.push_back(root->data);
            appendToVector(root->right, acc);
        }
    }
    
    inline vector<int> asVector(const Node* const root)
    {
        vector<int> acc;
        appendToVector(root, acc);
        return acc;
    }
    
    vector<int> intersectSorted(const vector<int>& a, const vector<int>& b)
    {
        vector<int> ret;
        ret.reserve(min(a.size(), b.size())); // can't be bigger than this
        
        const auto pend = a.cend(), qend = b.cend();
        auto p = a.cbegin(), q = b.cbegin();
        
        while (p != pend && q != qend) {
            if (*p == *q) {
                ret.push_back(*p);
                ++p;
                ++q;
            }
            else if (*p < *q) ++p;
            else ++q;
        }
        
        return ret;
    }
    
    void print(const vector<int>& a)
    {
        auto sep = "";
        for (const auto x : a) {
            cout << sep << x;
            sep = " ";
        }
        
        cout << '\n';
    }
}

/* Function should print common elements in given two trees */
void printCommon(Node *root1, Node *root2)
{
    print(intersectSorted(asVector(root1), asVector(root2)));
}
