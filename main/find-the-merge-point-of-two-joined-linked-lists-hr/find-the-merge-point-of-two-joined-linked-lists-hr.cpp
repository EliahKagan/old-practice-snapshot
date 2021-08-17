// Complete the findMergeNode function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    // Look head until one list ends, so we go that far in the other list.
    auto leader1 = head1, leader2 = head2;
    while (leader1 && leader2) {
        leader1 = leader1->next;
        leader2 = leader2->next;
    }

    // Advance whichever head has a longer tail, so they are the same length.
    for (; leader1; leader1 = leader1->next) head1 = head1->next;
    for (; leader2; leader2 = leader2->next) head2 = head2->next;

    // Now that tails are equal length, advance heads together until they meet.
    while (head1 != head2) {
        head1 = head1->next;
        head2 = head2->next;
    }

    // The problem description says they do in fact meet. So return that datum.
    assert(head1);
    return head1->data;
}
