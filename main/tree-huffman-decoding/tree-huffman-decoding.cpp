/* 
The structure of the node is

typedef struct node
{
    int freq;
    char data;
    node * left;
    node * right;
    
}node;

*/


void decode_huff(node * const root, const string s)
{
    auto cur = root;
    
    for (const auto b : s) {
        cur = (b == '0' ? cur->left : cur->right);
        
        if (cur->data != '\0') {
            cout << cur->data;
            cur = root;
        }
    }
}
