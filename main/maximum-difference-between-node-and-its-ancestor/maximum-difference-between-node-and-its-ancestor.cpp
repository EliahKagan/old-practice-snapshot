#include "maximum-difference-between-node-and-its-ancestor.h" //#include <bits/stdc++.h>
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




int maxDiff(Node *root);


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


     cout<<maxDiff(root)<<endl;

  }
  }
  return 0;
}


/* A binary tree node
struct Node
{
    int data;
    struct Node* left, * right;
}; */

namespace {
    template<typename T>
    inline T max3(const T x, const T y, const T z)
    {
        return max(x, max(y, z));
    }
    
    constexpr auto data_min = 1, data_max = 1000;
    constexpr auto diff_min = data_min - data_max;
    
    int maxDiff(const Node* const root, const int max_ancestor)
    {
        if (root == nullptr) return diff_min;
        
        const auto max_non_descendant = max(max_ancestor, root->data);
        
        return max3(max_ancestor - root->data,
                    maxDiff(root->left, max_non_descendant),
                    maxDiff(root->right, max_non_descendant));
    }
}

/* Your are required to 
complete this method*/
int maxDiff(Node* const root)
{
    return root == nullptr ? diff_min : maxDiff(root, diff_min);
}
