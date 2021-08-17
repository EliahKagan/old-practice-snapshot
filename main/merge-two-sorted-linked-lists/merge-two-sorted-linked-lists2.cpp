/* Link list Node
struct Node {
    int data;
    struct Node* next;
}; */

struct Node* SortedMerge(struct Node* const head1,
                         struct Node* const head2)
{
    if (head1 == nullptr) return head2;
    if (head2 == nullptr) return head1;

    const auto head = head2->data < head1->data ? head2 : head1;
    auto p = head, q = (p == head2 ? head1 : head2);
    
    for (; p->next != nullptr; p = p->next) {
        const auto bound = p->next->data;
        if (bound <= q->data) continue;

        auto r = q;
        while (r->next != nullptr && r->next->data <= bound) r = r->next;

        const auto next = p->next;
        p->next = q;
        q = r->next;
        r->next = next;

        if (q == nullptr) return head;
    }

    p->next = q;
    return head;
}
