/* Link list Node 
struct Node
{
    int data;
    Node* next;
};*/
/*You are required to complete below method*/
Node* deleteAllOccurances(Node *head, const int x)
{
    Node front {0, head};
    
    for (head = &front; head->next != nullptr; ) {
        if (head->next->data == x) {
            const auto old = head->next;
            head->next = head->next->next;
            delete old;
        }
        else head = head->next;
    }
    
    return front.next;
}
