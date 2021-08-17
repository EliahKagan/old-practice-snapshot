// Complete the reverse function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* reverse(SinglyLinkedListNode* head) {
    SinglyLinkedListNode* acc {};

    while (head) {
        const auto next = head->next;
        head->next = acc;
        acc = head;
        head = next;
    }

    return acc;
}
