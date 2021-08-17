// A program to check if a given binary tree is complete or not
#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_Q_SIZE 500

/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct node
{
    int data;
    struct node* left;
    struct node* right;
};

/* function prototypes for functions needed for Queue data
   structure. A queue is needed for level order tarversal */
struct node** createQueue(int *, int *);
void enQueue(struct node **, int *, struct node *);
struct node *deQueue(struct node **, int *);
bool isQueueEmpty(int *front, int *rear);

/* Given a binary tree, return true if the tree is complete
   else false */
bool isCompleteBT(struct node* root);

/*UTILITY FUNCTIONS*/
struct node** createQueue(int *front, int *rear)
{
  struct node **queue =
   (struct node **)malloc(sizeof(struct node*)*MAX_Q_SIZE);

  *front = *rear = 0;
  return queue;
}

void enQueue(struct node **queue, int *rear, struct node *new_node)
{
  queue[*rear] = new_node;
  (*rear)++;
}

struct node *deQueue(struct node **queue, int *front)
{
  (*front)++;
  return queue[*front - 1];
}

bool isQueueEmpty(int *front, int *rear)
{
   return (*rear == *front);
}

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct node* newNode(int data)
{
  struct node* node = (struct node*)malloc(sizeof(struct node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;

  return(node);
}

void insert(struct node *root,int n1,int n2,char lr)
 {
     if(root==NULL)
        return;
     if(root->data==n1)
     {
         switch(lr)
         {
          case 'L': root->left=newNode(n2);
                    break;
          case 'R': root->right=newNode(n2);
                    break;
         }
     }
     else
     {
         insert(root->left,n1,n2,lr);
         insert(root->right,n1,n2,lr);
     }
 }
// Driver program to test above functions
int main()
{
      /* Let us construct the following Binary Tree which
      is not a complete Binary Tree
            1
          /   \
         2     3
        / \     \
       4   5     6
    */
    int t;
    scanf("%d",&t);
    while(t--)
    {
    int n;
    scanf("%d",&n);
    struct node *root=NULL;
    while(n--)
    {
        char lr;
        int n1,n2;
        scanf("%d",&n1);
        scanf("%d",&n2);
        scanf(" %c",&lr);
        if(root==NULL)
        {
            root=newNode(n1);
            switch(lr){
                    case 'L': root->left=newNode(n2);
                    break;
                    case 'R': root->right=newNode(n2);
                    break;
                    }
        }
        else
        {
            insert(root,n1,n2,lr);
        }
    }
   
    if ( isCompleteBT(root) == true )
      printf ("Complete Binary Tree\n");
  else
      printf ("Not Complete Binary Tree\n");
    }
    return 0;
}

#include <queue>

// Given a binary tree, returns true iff the tree is complete.
bool isCompleteBT(struct node* root)
{
    std::queue<struct node*> q;
    for (q.push(root); q.front() != nullptr; q.pop()) { // BFS to first null
        q.push(q.front()->left);
        q.push(q.front()->right);
    }
    
    for (; !q.empty(); q.pop()) // The tree is complete iff only nulls remain.
        if (q.front() != nullptr) return false;
    
    return true;
}
