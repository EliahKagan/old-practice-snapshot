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
    using Link = struct node *;
    
    // Partitions a list. Returns a pointer to the last equal node.
    Link partition(Link head, const int pivot,
                   Link less, Link equal, Link greater)
    {
        for (; head; head = head->next) {
            if (head->data < pivot)
                less = less->next = head;
            else if (head->data == pivot)
                equal = equal->next = head;
            else
                greater = greater->next = head;
        }
        
        less->next = equal->next = greater->next = nullptr;
        return equal;
    }
    
    pair<Link, Link> quicksort_sublist(Link first)
    {
        if (!first->next) return {first, first};
        
        struct node less_pre {}, greater_pre {};
        auto last = partition(first->next, first->data,
                              &less_pre, first, &greater_pre);
        
        if (less_pre.next) {
            Link left_side_first {}, left_side_last {};
            tie(left_side_first, left_side_last) =
                    quicksort_sublist(less_pre.next);
            
            left_side_last->next = first;
            first = left_side_first;
        }
        
        if (greater_pre.next) {
            Link right_side_first {}, right_side_last {};
            tie(right_side_first, right_side_last) =
                    quicksort_sublist(greater_pre.next);
            
            last->next = right_side_first;
            last = right_side_last;
        }
        
        return {first, last};
    }
}

//you have to complete this function
void quickSort(Link *const head_ref)
{
    if (*head_ref)
        tie(*head_ref, ignore) = quicksort_sublist(*head_ref);
}
