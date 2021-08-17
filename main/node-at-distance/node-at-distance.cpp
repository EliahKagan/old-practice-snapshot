/* This function prints all nodes that are distance k from a leaf node
path[] --> Store ancestors of a node
visited[] --> Stores true if a node is printed as output. A node may be k
				distance away from many leaves, we want to print it once */
void kDistantFromLeafUtil(Node* node, int path[], bool visited[],
						  int pathLen, int k)
{
    if (node != nullptr) {
        //cout << '[' << node->key << ']';
        
        path[pathLen] = node->key;
        
        if (node->left == nullptr && node->right == nullptr && pathLen >= k) {
            const auto ancestor = path[pathLen - k];
            if (!visited[ancestor]) {
                visited[ancestor] = true;
                ++counter;
            }
        } else {
            kDistantFromLeafUtil(node->left, path, visited, pathLen + 1, k);
            kDistantFromLeafUtil(node->right, path, visited, pathLen + 1, k);
        }
    }
}
