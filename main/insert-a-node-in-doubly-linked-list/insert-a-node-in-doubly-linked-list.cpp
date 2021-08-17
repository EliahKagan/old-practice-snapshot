/* a node of the doubly linked list 
struct node
{
  int data;
  struct node *next;
  struct node *prev;
}; */

void addNode(node **const head_ref, int pos, const int data)
{
    ++pos;
    assert(head_ref != nullptr && pos >= 0);
    
    node start {0, *head_ref, nullptr}, *cur = &start;
    
    for (; pos != 0; --pos) {
        cur = cur->next;
        assert(cur != nullptr);
    }
    
    const auto next = new node{data, cur->next, cur};
    if (cur->next != nullptr) cur->next->prev = next;
    cur->next = next;
    
    const auto head = start.next;
    head->prev = nullptr;
    *head_ref = head;
}
