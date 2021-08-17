/* Link list node 
struct Node
{
    int data;
    Node* next;
}*/

// This function should delete node from linked list. The function
// may assume that node exists in linked list and is not last node
void deleteNode(Node *const node)
{
    assert(node != nullptr && node->next != nullptr);
    
    const auto next = node->next;
    *node = *next;
    delete next;
}
