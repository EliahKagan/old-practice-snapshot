/* Tree node structure  used in the program
 struct Node
 {
     int data;
     Node* left, *right;
}; */

/*You are required to complete below method */
int maxLevelSum(Node* root)
{
    auto max_sum = numeric_limits<int>::min();
    
    queue<Node*> q;
    for (q.push(root); !q.empty(); ) {
        auto sum = 0;
        
        for (auto width = q.size(); width != 0u; --width) {
            root = q.front();
            q.pop();
            if (root == nullptr) continue;
            
            sum += root->data;
            q.push(root->left);
            q.push(root->right);
        }
        
        if (max_sum < sum) max_sum = sum;
    }
    
    return max_sum;
}
