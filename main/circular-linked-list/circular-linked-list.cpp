/* Link list Node 
struct Node {
    int data;
    struct Node* next;
}; */


/* Should return true if linked list is circular, else false */
bool isCircular(struct Node *head)
{
    if (head == nullptr) return true;
    
    for (const Node* node = head->next; node != nullptr; node = node->next)
        if (node == head) return true;
    
    return false;
}
