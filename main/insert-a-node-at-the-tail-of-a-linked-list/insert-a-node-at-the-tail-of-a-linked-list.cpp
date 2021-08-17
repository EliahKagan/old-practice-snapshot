// Complete the insertNodeAtTail function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* insertNodeAtTail(SinglyLinkedListNode* const head,
                                       const int data) {
	const auto node = new SinglyLinkedListNode{data};
    if (!head) return node;

    auto cur = head;
    while (cur->next) cur = cur->next;
    cur->next = node;
    return head;
}
