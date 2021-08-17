// Complete the getNode function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
int getNode(SinglyLinkedListNode* head, const int positionFromTail) {
    auto length = 0;
    for (auto cur = head; cur; cur = cur->next) ++length;

    length = max(length - positionFromTail - 1, 0);
    while (length--) head = head->next;
    return head->data;
}
