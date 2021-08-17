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
    for (auto fast = head; fast && (fast = fast->next); fast = fast->next) {
        if (head == fast) return true;
        head = head->next;
    }

    return false;
}
