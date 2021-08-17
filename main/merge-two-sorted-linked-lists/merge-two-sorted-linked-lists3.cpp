/* Link list Node  
struct Node {
    int data;
    struct Node* next;
}; */

struct Node* SortedMerge(struct Node* head1, struct Node* head2)
{
    Node start {0, nullptr}, *cur = &start;
    
    for (; head1 != nullptr && head2 != nullptr; cur = cur->next) {
        if (head1->data < head2->data) {
            cur->next = head1;
            head1 = head1->next;
        } else {
            cur->next = head2;
            head2 = head2->next;
        }
    }
    
    cur->next = (head1 == nullptr ? head2 : head1);
    return start.next;
}
