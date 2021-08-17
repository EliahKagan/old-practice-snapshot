/* Link list Node
struct Node {
    int data;
    struct Node* next;
}; */

namespace {
    std::size_t countNodes(struct Node *head) // assumes non-empty list
    {
        std::size_t i {1u};
        for (; head->next != nullptr; head = head->next) ++i;
        return i;
    }

    Node *walk(struct Node *head, std::size_t n) // assumes n in bounds
    {
        for (; n != 0u; --n) head = head->next;
        return head;
    }
}

/* Should return data of intersection point of two linked
   lists head1 and head2.
   If there is no intersecting point, then return -1. */
int intersectPoint(struct Node* head1, struct Node* head2)
{
    constexpr auto not_found = -1;
    if (head1 == nullptr || head2 == nullptr) return not_found;

    auto n1 = countNodes(head1), n2 = countNodes(head2);
    if (n1 < n2) {
        std::swap(n1, n2);
        std::swap(head1, head2);
    }

    for (head1 = walk(head1, n1 - n2); head1 != head2; head1 = head1->next)
        head2 = head2->next;

    return head1 == nullptr ? not_found : head1->data;
}
