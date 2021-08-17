/* A tree Node has data, pointer to left child
   and a pointer to right child  
struct Node
{
    int data;
    Node* left;
    Node* right;
}; */

namespace {
    vector<int> levelOrderRtl(const Node* const root)
    {
        vector<int> a;
        
        queue<const Node*> q;
        for (q.push(root); !q.empty(); q.pop()) {
            if (q.front() != nullptr) {
                a.push_back(q.front()->data);
                q.push(q.front()->right);
                q.push(q.front()->left);
            }
        }
        
        return a;
    }
}

void reversePrint(Node* const root)
{
    const auto a = levelOrderRtl(root);
    for_each(a.crbegin(), a.crend(), [](const int x) { cout << x << ' '; });
}
