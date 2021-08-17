// Complete the reverse function below.

/*
 * For your reference:
 *
 * DoublyLinkedListNode {
 *     int data;
 *     DoublyLinkedListNode* next;
 *     DoublyLinkedListNode* prev;
 * };
 *
 */
DoublyLinkedListNode* reverse(DoublyLinkedListNode* head) {
    if (!head) return nullptr;

    for (; ; ) {
        swap(head->next, head->prev);
        if (!head->prev) break;
        head = head->prev;
    }

    return head;
}
