// Complete the deleteNode function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* deleteNode(SinglyLinkedListNode* head, int position) {
    SinglyLinkedListNode sentinel {0};
    sentinel.next = head;

    head = &sentinel;
    while (position-- > 0 && head->next) head = head->next;

    const auto next = head->next;
    head->next = next->next;
    delete next;

    return sentinel.next;
}
