
namespace {
    struct node* makeNode(const int data, struct node* const next)
    {
        // The calling code creates nodes freeable by free(), so I should too.
        const auto p = static_cast<struct node*>(malloc(sizeof(struct node)));
        if (p == nullptr) throw bad_alloc{};
        
        p->data = data;
        p->next = next;
        
        return p;
    }
}

/*
structure of the node of the list is as
struct node
{
	int data;
	struct node* next;
};
*/
void sortedInsert(struct node** head_ref, int data)
{
    struct node start {0, *head_ref};
    
    auto p = &start;
    while (p->next != nullptr && p->next->data < data) p = p->next;
    p->next = makeNode(data, p->next);
    
    *head_ref = start.next;
}
