namespace {
    // Insert all the data from the list src into the set dest.
    // This is a helper function for makeUnion().
    inline void put(set<int>& dest, const struct node* src)
    {
        for (; src != nullptr; src = src->next) dest.insert(src->data);
    }

    // Create a new list node with the specified data and next pointer.
    // This is a helper function for makeList().
    inline struct node* makeNode(const int data, struct node* const next)
    {
        // The G4G test harness makes nodes freeable with free(); so I am too.
        // (Alternative: I could never make a node, just reuse what I get.)
        const auto p = static_cast<struct node*>(malloc(sizeof(struct node)));
        if (p == nullptr) throw std::bad_alloc{};

        p->data = data;
        p->next = next;

        return p;
    }

    // Create a new list, in nondecreasing order of data, from the set vals.
    // This is a helper function for makeList().
    struct node* makeList(const set<int>& vals)
    {
        struct node* head {nullptr};

        for_each(vals.crbegin(), vals.crend(), [&](const int data) {
            head = makeNode(data, head);
        });

        return head;
    }
}

/*
structure of the node is as
struct node
{
	int data;
	struct node* next;
};
*/
struct node* makeUnion(struct node* head1, struct node* head2)
{
    set<int> vals;
    put(vals, head1);
    put(vals, head2);

    return makeList(vals);
}
