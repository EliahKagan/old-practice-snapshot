// Complete the has_cycle function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
bool has_cycle(const SinglyLinkedListNode* head) {
    auto fast = head;

    while (fast) {
        fast = fast->next;
        if (!fast) break;

        fast = fast->next;

        if (head == fast) return true;
        head = head->next;
    }

    return false;
}
