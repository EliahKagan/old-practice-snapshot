#include "convert-ternary-expression-to-binary-tree-fast.h" //#include<bits/stdc++.h>
using namespace std;
struct Node{
	char data;
	Node *left,*right;
};
Node *newNode(char Data)
{
    Node *new_node = new Node;
    new_node->data = Data;
    new_node->left = new_node->right = NULL;
    return new_node;
}
void preorder(Node *root){
	if(root==NULL)
		return;
	cout<<root->data<<" ";
	preorder(root->left);
	preorder(root->right);
}
Node *convertExpression(string str,int i);
int main(){
	int t;
	cin>>t;
	while(t--){
		string str;
		cin>>str;
		Node *root=convertExpression(str,0);
		preorder(root);
		cout<<endl;
	}
}

namespace {
    using It = string::const_iterator;
    
    inline It findOutermostMatchingColon(It p) // assumes there is one
    {
        for (auto depth = 0; ; ++p) {
            switch (*p) {
            case '?':
                ++depth;
                break;
            
            case ':':
                if (--depth == 0) return p;
                break;
                
            default:
                break; // ignore other characters
            }
        }
    }
}

/*Complete the function below
Node is as follows
struct Node{
	char data;
	Node *left,*right;
};
*/
Node *convertExpression(const string expr, const int i)
{
    const function<Node *(It, It)>
    dfs {[&dfs](const It first, const It last) -> Node * {
        switch (last - first) {
        case 0:
            return nullptr;
            
        case 1:
            return new Node{*first, nullptr, nullptr};
            
        default:
            const auto p = next(first);
            const auto q = findOutermostMatchingColon(p);
            return new Node{*first, dfs(next(p), q), dfs(next(q), last)};
        }
    }};
    
    return dfs(expr.cbegin() + i, expr.cend());
}
