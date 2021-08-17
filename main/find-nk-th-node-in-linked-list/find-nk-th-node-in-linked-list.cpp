/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*The structure of the node is
struct node
{
    int data;
    struct node *next;
};*/

namespace {
    int length(const struct node *head)
    {
        auto len = 0;
        for (; head; head = head->next) ++len;
        return len;
    }

    const struct node *advance_by(const struct node *head, int distance)
    {
        for (; distance > 0; --distance) head = head->next;
        return head;
    }
}

int fractional_node(struct node *const head, const int k)
{
    const auto n = length(head);

    auto d = n / k;
    if (n % k == 0) --d;
    return advance_by(head, d)->data;
}
