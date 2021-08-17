#include "duplicate-subtree-in-binary-tree.h" //#include <bits/stdc++.h>
using namespace std;

struct Node
{
  char data;
  struct Node* left;
  struct Node* right;
};

struct Node* insert(struct Node* root,char data)
{
    if(root==NULL){
    root= new struct Node;
    root->data=data;
    root->left=NULL;
    root->right=NULL;
    return root;
    }

    else if(root->data<data)
    root->right=insert(root->right,data);

    else if(root->data>data)
    root->left=insert(root->left,data);

  return root;
}







struct Node* insertString(struct Node* root,string s, int *j)
{

    if((*j)>=s.length())
    return NULL;

	          if(s[*j]=='(')
	          (*j)++;


	         if(s[*j]!='('&&s[*j]!=')'){
	             
	             char n=0;
	             n = s[*j];
             (*j)++;

	          root=insert(root,n);

	          //cout<<"root->data="<<root->data<<endl;

	         // (*j)++;

	          if(s[*j]==')'){
                root->left=NULL;
              root->right=NULL;
              //cout<<"root->data="<<root->data<<endl;
              //cout<<"root->left=NULL\n";
              //cout<<"root->right=NULL\n";
              return root;
	          }

	         }

             if(s[*j]=='(')
	          (*j)++;

	          if(s[*j]==')'){
	            //  cout<<"root->data="<<root->data<<endl;
              //cout<<"root->left=NULL\n";
	          root->left=NULL;
	          }
              else{
                //    cout<<"root->left->parent->data="<<root->data<<endl;
	          root->left=insertString(root->left,s,j);
              }

//cout<<"right\n";

              while(s[*j]==')')
	          (*j)++;

	          if(s[*j]=='(')
	          (*j)++;

	          if(s[*j]==')'){
      //        cout<<"root->data="<<root->data<<endl;
        //      cout<<"root->right=NULL\n";
	          root->right=NULL;
	          (*j)++;
	          }
	          else{
          //    cout<<"root->right->parent->data"<<root->data<<endl;
              root->right=insertString(root->right,s,j);
	          }
return root;
}

void print(struct Node* root)
{

    if(root==NULL)
        return;


    print (root->left);
    cout<<root->data<<endl;
    print(root->right);

}
bool dupSub(Node *root);

int main() {
	//code
	int i,j,k,T ,level;
	char s[500];

	   cin>>T;

	   for(i=0;i<T;i++)
	   {
	     // cin>>level;

	      cin>>s;

	      int j=0;

	      struct Node* root=NULL;

	      root=insertString(root,s,&j);
	   
        cout<<dupSub(root)<<endl;

	  

	   }




	return 0;
}

/*The structure of the Binary Tree Node  is
struct Node
{
  char data;
  struct Node* left;
  struct Node* right;
};*/

namespace {
    using SharedString = shared_ptr<const string>;
    
    struct SharedStringHash {
        size_t operator()(const SharedString p) const { return hash_(*p); }

    private:
        const hash<string> hash_ {};
    };
    
    struct SharedStringEqual {
        bool operator()(const SharedString p, const SharedString q) const
        {
            return *p == *q;
        }
    };
    
    using Memo = unordered_set<SharedString, SharedStringHash,
                                             SharedStringEqual>;
    
    inline SharedString represent(const char data, const SharedString left,
                                                   const SharedString right)
    {
        static constexpr string::size_type punct_len {3u}; // "(a", ")"
        
        const auto repr = make_shared<string>();
        repr->reserve(left->size() + right->size() + punct_len);
        
        *repr += '(';
        *repr += data;
        *repr += *left;
        *repr += *right;
        *repr += ')';
        
        return repr;
    }
    
    inline bool isLeafOrEmpty(const SharedString repr)
    {
        static constexpr string::size_type leaf_len {7u}; // "(a()())"
        
        return repr->size() <= leaf_len;
    }
    
    // Serializes depth-first from cur, adding "nontrivial" representations to
    // memo. Stops and returns a null handle if a duplicate is found.
    SharedString serializeIfUnique(const Node* const root, Memo& memo)
    {
        static const auto empty_tree_repr = make_shared<const string>("()");
        if (root == nullptr) return empty_tree_repr;
        
        const auto left = serializeIfUnique(root->left, memo);
        if (!left) return nullptr;
        
        const auto right = serializeIfUnique(root->right, memo);
        if (!right) return nullptr;
        
        // return repr iff it is trivial or not already in memo
        const auto repr = represent(root->data, left, right);
        if (isLeafOrEmpty(repr) || memo.insert(repr).second) return repr;
        return nullptr;
    }
}

/*This function returns true if the tree contains 
a duplicate subtree of size 2 or more else returns false*/
bool dupSub(Node* const root)
{
    Memo memo;
    return !serializeIfUnique(root, memo);
}
