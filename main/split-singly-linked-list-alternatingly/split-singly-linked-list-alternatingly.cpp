
namespace {
    inline void appendOne(struct node*& dest, struct node*& src)
    {
        const auto next = src->next;
        src->next = nullptr;
        dest = dest->next = src;
        src = next;
    }
}

/*
structure of node is as
struct node
{
	int data;
	struct node* next;
};
*/
void alternatingSplitList(struct node* head, struct node** aRef,
                                             struct node** bRef)
{
    struct node a {0, nullptr}, b {0, nullptr};
    
    for (auto p = &a, q = &b; head != nullptr; ) {
        appendOne(p, head);
        if (head != nullptr) appendOne(q, head);
    }
    
    *aRef = a.next;
    *bRef = b.next;
}
