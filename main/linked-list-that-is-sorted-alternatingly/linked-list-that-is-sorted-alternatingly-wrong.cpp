/*Structure of Node of the linked list is as
struct Node
{
	int data;
	struct Node *next;
};
*/

namespace {
    void print(Node* p)
    {
        cout << "[ ";
        for (; p != nullptr; p = p->next) cout << p->data << ' ';
        cout << "]\n";
    }
    
    void swap_next_two(Node* const p)
    {
        const auto q = p->next, r = q->next, s = r->next;
        p->next = r;
        r->next = q;
        q->next = s;
    }
}

void sort(Node **head)
{
    assert (*head != nullptr);
    
    Node fake_head {0, *head}, *p = &fake_head;
    if (p->next == nullptr) return;
    
    for (; p->next->next != nullptr; p = p->next) {
        print(fake_head.next);
        
        if (p->next->data > p->next->next->data) {
            swap_next_two(p);
        }
    }
    
    *head = fake_head.next;
}
