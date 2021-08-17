/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/


/* a node of the singly linked list
struct node
{
    int data;
    struct node *next;
}; */

namespace {
    void quicksort_range(struct node **const first_ref,
                         struct node **const last_ref)
    {
        auto first = *first_ref, last = *last_ref;
        if (first == last) return;

        const auto pivot = first->data;
        auto equal_cur = first;
        struct node less_sentinel {}, greater_sentinel {};
        auto less_cur = &less_sentinel, greater_cur = &greater_sentinel;



        ////
        for (auto head = first->next; head; head = head->next) {
            if (head->data < pivot)
                less_cur = less_cur->next = head;
            else if (cur->data == pivot)
                equal_cur = equal_cur->next = head;
            else
                greater_cur = greater_cur->next = head;
        }

        if (less_sentinel->next) {
            quicksort_range(&less_sentinel.next, &less_cur);
            *first_ref = less_sentinel.next;
            less_cur->next = first;
        }

        if (greater_sentinel->next) {
            quicksort_range(&greater_sentinel.next, &greater_cur);


        }

        equal_cur->next = greater_sentinel.next;


    }
}

//you have to complete this function
void quickSort(struct node **const head_ref)
{
    auto first = *head_ref;
    if (!first) return;

    auto last = first;
    while (last->next) last = last->next;

    quicksort_range(&first, &last);
    assert(last && !last->next);
    *head_ref = first;
}
