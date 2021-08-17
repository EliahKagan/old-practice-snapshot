/* a node of the doubly linked list */
/*struct node
{
  int data;
  struct node *next;
  struct node *prev;
};*/

#include <utility>

void reverse(struct node **head_ref)
{
    auto& head = *head_ref;
    if (head == nullptr) return;

    for (; ; ) {
        std::swap(head->next, head->prev);
        if (head->prev == nullptr) break;
        head = head->prev;
    }
}
