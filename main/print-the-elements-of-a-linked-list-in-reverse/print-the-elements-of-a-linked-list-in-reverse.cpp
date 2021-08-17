// Complete the reversePrint function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
void reversePrint(const SinglyLinkedListNode* const head) {
    if (head) {
        reversePrint(head->next);
        cout << head->data << '\n';
    }
}
