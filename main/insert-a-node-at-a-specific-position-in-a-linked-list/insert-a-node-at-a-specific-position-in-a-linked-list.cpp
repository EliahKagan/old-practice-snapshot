// Complete the insertNodeAtPosition function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* head,
                                           const int data, int position) {
    SinglyLinkedListNode sentinel {0};
    sentinel.next = head;

    head = &sentinel;
    while (position-- > 0 && head->next) head = head->next;

    const auto node = new SinglyLinkedListNode{data};
    node->next = head->next;
    head->next = node;

    return sentinel.next;
}
