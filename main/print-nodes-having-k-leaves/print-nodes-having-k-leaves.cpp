#include "print-nodes-having-k-leaves.h" //#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int data ;
    struct Node * left, * right ;
};
int flag=0;
struct Node * newNode(int data)
{
    struct Node * node = new Node;
    node->data = data;
    node->left = node->right = NULL;
    return (node);
}
void insert(Node *root,int a,int a1,char lr){
		if(root==NULL)
			return;
		if(root->data==a)
		{
			switch(lr){
					case 'L':root->left=newNode(a1);
					break;
					case 'R':root->right=newNode(a1);
					break;
				}
		}
		else {
			insert(root->left,a,a1,lr);
			insert(root->right,a,a1,lr);
		}
	}
int btWithKleaves(struct Node *ptr,int k);
	int main(){
		int t;
		char lr;
		cin>>t;
		while(t-->0){
			int n,k;
			int a,a1;
			cin>>n>>k;
			Node* root=NULL;
			if(n==0||n==1)
			{
				cout<<"-1"<<endl;
				continue;
			}
			for(int i=0;i<n;i++){
				cin>>a>>a1;
				fflush(stdin);
				cin>>lr;
				if(root==NULL){
					root=newNode(a);
					switch(lr){
						case 'L':root->left=newNode(a1);
						break;
						case 'R':root->right=newNode(a1);
						break;
					}
				}
				else{
					insert(root,a,a1,lr);
				}
			}
			btWithKleaves(root,k);
		}
	}

/*The Node is defined as follows:
struct Node
{
    int data ;
    struct Node * left, * right ;
};*/

/*You are required to complete below method */
int btWithKleaves(Node *const head, const int k)
{
    //assert(k > 0);

    auto found = false;

    const function<int(const Node*)>
    dfs {[&dfs, &found, k](const Node *const p) {
        if (p == nullptr) return 0;
        
        if (p->left == nullptr && p->right == nullptr) return 1;
        
        const auto cnt = dfs(p->left) + dfs(p->right);

        if (cnt == k) {
            found = true;
            cout << p->data << ' ';
        }
        
        return cnt;
    }};

    const auto ret = dfs(head);
    
    if (found) cout << '\n';
    else cout << "-1\n";
    
    return ret;
}
