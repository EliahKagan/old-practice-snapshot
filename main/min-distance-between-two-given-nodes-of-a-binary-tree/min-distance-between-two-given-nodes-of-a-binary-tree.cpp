#include "min-distance-between-two-given-nodes-of-a-binary-tree.h" // #include <bits/stdc++.h>
using namespace std;

/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};


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

int findDist(Node* ,int ,int );


/* Driver program to test size function*/
int main()
{
  int t;
  struct Node *child;
  scanf("%d\n", &t);
  while (t--)
  {
     map<int, Node*> m;
     int n;
     scanf("%d\n",&n);
     struct Node *root = NULL;
     if(n==1)
     {
        int a;
        cin>>a;
        cout<<a<<endl;
     }else{
     while (n--)
     {
        Node *parent;
        char lr;
        int n1, n2;
        scanf("%d %d %c", &n1, &n2, &lr);
      //  cout << n1 << " " << n2 << " " << (char)lr << endl;
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
     int a,b;
     cin>>a>>b;

     cout<<findDist(root,a,b)<<endl;

  }
  }
  return 0;
}

/* A binary tree node
struct Node
{
    int data;
    Node* left, * right;
}; */

namespace {
    using NodeParents = unordered_map<const Node*, const Node*>;
    
    using NodeDepths = unordered_map<const Node*, int>;
    
    NodeParents
    getNodeParentsAndKeyDepths(const Node* root, const int a, const int b,
                               NodeDepths& as, NodeDepths& bs)
    {
        NodeParents parents;
        queue<const Node*> q;
        
        const auto recordNeighbors = [&root, &parents, &q](const Node* child) {
            if (child != nullptr) {
                parents.emplace(child, root);
                q.push(child);
            }
        };
        
        q.push(root);
        for (auto depth = 0; !q.empty(); ++depth) {
            for (auto width = q.size(); width != 0u; --width) {
                root = q.front();
                q.pop();
                
                if (root->data == a) as.emplace(root, depth);
                if (root->data == b) bs.emplace(root, depth);
                
                recordNeighbors(root->left);
                recordNeighbors(root->right);
            }
        }
        
        return parents;
    }
    
    inline int getDist(const NodeParents& parents,
                       const Node* lower, const Node* upper, int rise)
    {
        auto hops = rise;
        
        while (rise-- != 0) lower = parents.at(lower);
        
        for (; lower != upper; hops += 2) {
            lower = parents.at(lower);
            upper = parents.at(upper);
        }
        
        return hops;
    }
}

/* Should return minimum distance between a and b 
   in a tree with given root*/
int findDist(Node* root, const int a, const int b)
{
    NodeDepths as, bs;
    const auto parents = getNodeParentsAndKeyDepths(root, a, b, as, bs);
    
    auto min_hops = numeric_limits<int>::max();
    
    for (const auto& a_pair : as) {
        const Node* a_node;
        int a_depth;
        tie(a_node, a_depth) = a_pair;
        
        for (const auto& b_pair : bs) {
            const Node* b_node;
            int b_depth;
            tie(b_node, b_depth) = b_pair;
            
            const auto rise = a_depth - b_depth;
            
            const auto hops =
                    (rise < 0 ? getDist(parents, b_node, a_node, -rise)
                              : getDist(parents, a_node, b_node, rise));
            
            if (min_hops > hops) min_hops = hops;
        }
    }
    
    return min_hops == numeric_limits<int>::max() ? -1 : min_hops;
}
