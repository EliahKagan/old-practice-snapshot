struct Node
{
    int data;
    struct Node *next;
};

namespace {
    Node* Tail(Node* head)
    {
        return head->next == nullptr ? head : Tail(head->next);
    }
}

Node* Insert(Node* head, int data)
{
    auto node = new Node{data, nullptr};
    
    if (head == nullptr) return node;

    auto tail = Tail(head);
    tail->next = node;
    return head;
}
