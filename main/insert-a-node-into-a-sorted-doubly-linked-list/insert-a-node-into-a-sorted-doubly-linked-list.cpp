// Complete the sortedInsert function below.

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
DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* head, const int data) {
    DoublyLinkedListNode sentinel {0};
    sentinel.next = head;

    head = &sentinel;
    while (head->next && head->next->data < data) head = head->next;

    const auto node = new DoublyLinkedListNode{data};
    node->prev = head;
    node->next = head->next;

    if (head->next) head->next->prev = node;
    head->next = node;

    return sentinel.next;
}
