// Complete the compare_lists function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
bool compare_lists(const SinglyLinkedListNode* head1,
                   const SinglyLinkedListNode* head2) {
    for (; ; ) {
        if (head1 == head2) return true;
        if (!head1 || !head2 || head1->data != head2->data) return false;
        head1 = head1->next;
        head2 = head2->next;
    }
}
