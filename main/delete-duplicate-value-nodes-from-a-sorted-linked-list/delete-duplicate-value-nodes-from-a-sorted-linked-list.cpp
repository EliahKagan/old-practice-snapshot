// Complete the removeDuplicates function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* removeDuplicates(SinglyLinkedListNode* const head) {
    for (auto cur = head; cur; cur = cur->next) {
        while (cur->next && cur->data == cur->next->data) {
            const auto next = cur->next;
            cur->next = next->next;
            delete next;
        }
    }

    return head;
}
