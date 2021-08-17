/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

//User function Template for C++
struct node *update(struct node *start, int p)
{
    if (!start) return nullptr;

    auto len = 1;
    auto cur = start;
    for (; cur->next; cur = cur->next) ++len;

    assert(!start->prev);
    start->prev = cur;
    cur->next = start;

    for (p %= len; p != 0; --p) start = start->next;
    start->prev = start->prev->next = nullptr;
    return start;
}
