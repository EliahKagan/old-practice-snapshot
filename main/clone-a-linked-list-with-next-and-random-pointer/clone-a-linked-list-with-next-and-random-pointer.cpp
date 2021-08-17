/*  the node structure is as follows 
struct Node
{
int data;
Node* next;
Node* arb;
};*/

// Should return the head of the copied linked list the 
//output will be 1 if successfully copied
Node* copyList(Node* head)
{
    Node start {0, head, nullptr};
    
    unordered_map<Node*, Node*> m {make_pair<Node*, Node*>(nullptr, nullptr)};
    for (auto cur = &start; head != nullptr; head = head->next)
        m.emplace(head, cur = cur->next = new Node{*head});
    
    for (auto cur = start.next; cur != nullptr; cur = cur->next)
        cur->arb = m.at(cur->arb);
    
    return start.next;
}
