struct Node
{
    int data;
    struct Node *next;
};

Node* Insert(Node* head, int data)
{
    return head = new Node{data, head};
}
