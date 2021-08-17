struct Node
{
    int data;
    struct Node *next;
};

Node* Delete(Node* head, int position)
{
    auto node = head;

    if (position <= 0) {
        if (position == 0) {
            head = head->next;
            delete node;
        }
    } else {
        while (--position != 0) node = node->next;
        auto tmp = node->next;
        node->next = node->next->next;
        delete tmp;
    }

    return head;
}
