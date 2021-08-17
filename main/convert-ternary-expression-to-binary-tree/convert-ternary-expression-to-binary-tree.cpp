#include "convert-ternary-expression-to-binary-tree.h" //#include<bits/stdc++.h>
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
    using It = std::string::const_iterator;
    
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
    
    Node *convertExpression(string expr)
    {
        switch (expr.size()) {
        case 0u:
            return nullptr;
        
        case 1u:
            return new Node{expr.front(), nullptr, nullptr};
        
        default:
            const auto p = next(expr.cbegin());
            const auto q = findOutermostMatchingColon(p);
            
            string lsub (next(p), q), rsub (next(q), expr.cend());
            
            return new Node{expr.front(), convertExpression(move(lsub)),
                                          convertExpression(move(rsub))};
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
Node *convertExpression(string expr, int)
{
    return convertExpression(expr);
}
