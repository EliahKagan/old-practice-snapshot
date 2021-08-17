/* Link list Node 
struct Node
{
    int data;
    Node* next;
};*/

/*You are required to complete below method*/
Node* deleteNode(Node *head, int x)
{
    Node front {0, head};
    
    for (head = &front; --x > 0; ) head = head->next;
    
    const auto next = head->next->next;
    delete head->next;
    head->next = next;
    
    return front.next;
}
