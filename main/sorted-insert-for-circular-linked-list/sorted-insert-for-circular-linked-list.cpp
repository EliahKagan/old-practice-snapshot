/* structure for a node */
/*
struct Node
{
  int data;
  Node *next;
};
 */
void sortedInsert(Node** const head_ref, const int x)
{
    const auto head = *head_ref;
    
    if (head == nullptr) {
        auto new_head = new Node{x, nullptr};
        *head_ref = new_head->next = new_head;
    }
    else if (x < head->data) {
        auto new_head = new Node{x, head}, tail = head;
        while (tail->next != head) tail = tail->next;
        *head_ref = tail->next = new_head;
    } else {
        auto cur = head;
        while (cur->next != head && cur->next->data <= x) cur = cur->next;
        cur->next = new Node{x, cur->next};
    }
}
