#include<stdio.h>
#include<stdlib.h>


/* Link list node */
struct node
{
    int data;
    struct node* next;
}*head;

struct node *reverse (struct node *head, int k);

/* Reverses the linked list in groups of size k and returns the
   pointer to the new head node. */

/* UTILITY FUNCTIONS */
/* Function to push a node */

  void insert()
{
    int n,value,i;
    scanf("%d",&n);
    struct node *temp = NULL; // added = NULL
    for(i=0;i<n;i++)
    {
        scanf("%d",&value);
        if(i==0)
        {
            head=(struct node *) malloc( sizeof(struct node) );
            head->data=value;
            head->next=NULL;
            temp=head;
            continue;
        }
        else
        {
            temp->next= (struct node *) malloc( sizeof(struct node) );
            temp=temp->next;
            temp->data=value;
            temp->next=NULL;
        }
    }
}

/* Function to print linked list */
void printList(struct node *node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
printf("\n");
}

/* Drier program to test above function*/
int main(void)
{
    /* Start with the empty list */

    int t,k,value,n;
     /* Created Linked list is 1->2->3->4->5->6->7->8->9 */
     scanf("%d",&t);
     while(t--)
     {
     insert();
     scanf("%d",&k);
     head = reverse(head, k);
     printList(head);
     }
     return(0);
}
/*
  Reverse a linked list
  The input list will have at least one element  
  Return pointer to head of reverse linked list 
  Node is defined as 
  struct node
  {
     int data;
     struct Node *next;
  }
*/

// Terminate the list after the first k nodes, and return a list made of the
// remaining nodes. If there are fewer than (or equal to) k nodes in the list,
// then the list is not modified and NULL is returned.
static struct node *split(struct node* head, int k)
{
    for (; k > 1 && head != NULL; --k) head = head->next;
    if (head == NULL) return NULL;

    struct node *const next = head->next;
    head->next = NULL;
    return next;
}

// Reverses the list completely, in the usual way. Returns the new head.
static struct node *rev(struct node* head)
{
    struct node *acc = NULL;
    
    while (head != NULL) {
        struct node *const next = head->next;
        head->next = acc;
        acc = head;
        head = next;
    }
    
    return acc;
}

// Viewing the list as a sequence of groups of length k, reverses each group,
// but the groups sequence with respect to one another is kept the same. It's
// unfortunate _this_ function is the one called reverse(), but the task
// requirements prohibit renaming it.
struct node *reverse(struct node *head, const int k)
{
    struct node dummy = { 0, NULL }, *back = &dummy;
    
    while (head != NULL) {
        struct node *const next_group = split(head, k);
        back->next = rev(head);
        back = head; // head was the first of this group, so now is the last
        head = next_group;
    }
    
    return dummy.next;
}
