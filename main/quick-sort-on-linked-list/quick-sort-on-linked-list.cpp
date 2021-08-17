#include <iostream>
#include <cstdio>
using namespace std;

/* a node of the singly linked list */
struct node
{
    int data;
    struct node *next;
};
 node* newNode(int key)
{
    node *temp = new node;
    temp->data = key;
    temp->next = NULL;
    return temp;
}
/* A utility function to insert a node at the beginning of linked list */
void push(struct node** head_ref, int new_data)
{
    /* allocate node */
    struct node* new_node = new node;

    /* put in the data  */
    new_node->data  = new_data;

    /* link the old list off the new node */
    new_node->next = (*head_ref);

    /* move the head to point to the new node */
    (*head_ref)    = new_node;
}

/* A utility function to print linked list */
void printList(struct node *node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}
void quickSort(struct node **headRef);
int main()
{
	int t,n,x;
	cin>>t;
	while(t--){


        cin>>n;n=n-1;
		cin>>x;
        node *temp,*head = newNode(x);
        temp=head;
        while(n--)
        {
			cin>>x;
          temp->next=newNode(x);
          temp=temp->next;
			}

    quickSort(&head);

    printList(head);
 while(head!= NULL){
     temp=head;
     head=head->next;
     free(temp);

 }
	}
    return 0;
}

/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/


/* a node of the singly linked list
struct node
{
    int data;
    struct node *next;
}; */

#include <tuple>
#include <utility>

namespace {
    using Link = struct node*;

    // Partitions a list into sublists that are less than, equal to, and
    // greater than a specified pivot.
    void partition(const int pivot, Link head,
                   Link& less_cur, Link& equal_cur, Link& greater_cur)
    {
        for (; head; head = head->next) {
            if (head->data < pivot)
                less_cur = less_cur->next = head;
            else if (head->data == pivot)
                equal_cur = equal_cur->next = head;
            else
                greater_cur = greater_cur->next = head;
        }

        less_cur->next = equal_cur->next = greater_cur->next = nullptr;
    }

    // Quicksorts a nonempty list and gives points to its first and last nodes.
    // The head node is used as the pivot (and is thus called "equal_first").
    pair<Link, Link> quicksort_to_range(Link equal_first)
    {
        if (!equal_first->next) return {equal_first, equal_first};

        struct node less_pre {}, greater_pre {};
        auto less_cur = &less_pre, greater_cur = &greater_pre;
        auto equal_cur = equal_first;

        partition(equal_first->data, equal_first->next,
                  less_cur, equal_cur, greater_cur);

        auto first = equal_first, last = equal_cur; // for results

        if (less_pre.next) {
            Link mid {};
            tie(first, mid) = quicksort_to_range(less_pre.next);
            mid->next = equal_first;
        }

        if (greater_pre.next)
            tie(equal_cur->next, last) = quicksort_to_range(greater_pre.next);

        return {first, last};
    }
}

//you have to complete this function
void quickSort(Link *const head_ref)
{
    if (*head_ref)
        tie(*head_ref, ignore) = quicksort_to_range(*head_ref);
}
