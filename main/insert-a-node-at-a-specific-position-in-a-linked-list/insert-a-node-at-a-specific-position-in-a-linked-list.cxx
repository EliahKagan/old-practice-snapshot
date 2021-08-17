struct Node
{
    int data;
    struct Node *next;
};

Node* InsertNth(Node* head, int data, int position)
{
    if (position <= 0) return new Node{data, new Node{2, nullptr}};

    auto node = head;
    while (node->next != nullptr && --position > 0) node = node->next;
    
    node->next = new Node{data, node->next};
    
    return head;
}
