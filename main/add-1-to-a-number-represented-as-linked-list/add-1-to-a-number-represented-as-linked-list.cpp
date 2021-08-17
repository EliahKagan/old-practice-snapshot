/* Node structure
struct Node
{
    int data;
    struct Node* next;
}; */

// Should rearrange given linked list such that all even
// positioned Nodes are before odd positioned.
// Returns new head of linked List.
Node *addOne(Node *head)
{
    constexpr auto base = 10, digit_max = base - 1;
    
    stack<Node *> digits;
    for (auto cur = head; cur != nullptr; cur = cur->next) digits.push(cur);
    
    for (; !digits.empty() && digits.top()->data == digit_max; digits.pop())
        digits.top()->data = 0;
    
    if (digits.empty()) return new Node{1, head};
    
    ++digits.top()->data;
    return head;
}
