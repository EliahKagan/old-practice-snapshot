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
int getNode(SinglyLinkedListNode* head, int positionFromTail) {
    auto leader = head;
    while (positionFromTail-- > 0) leader = leader->next;

    for (; leader->next; leader = leader->next) head = head->next;
    return head->data;
}
