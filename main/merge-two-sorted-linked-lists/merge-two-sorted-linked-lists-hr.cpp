// Complete the mergeLists function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1,
                                 SinglyLinkedListNode* head2) {
    SinglyLinkedListNode sentinel {0};
    auto cur = &sentinel;

    for (; head1 && head2; cur = cur->next) {
        if (head2->data < head1->data) {
            cur->next = head2;
            head2 = head2->next;
        } else {
            cur->next = head1;
            head1 = head1->next;
        }
    }

    cur->next = (head1 ? head1 : head2);
    return sentinel.next;
}
