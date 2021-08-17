#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
/* Linked list node */
struct node
{
    int data;
    struct node* next;
};
 void reorderList(struct node* head) ;
/* Function to create a new node with given data */
struct node *newNode(int data)
{
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}
void printList(struct node *node)
{
    while(node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}
void freeList(struct node *head)
{
	struct node* temp;
    while(head != NULL)
    {
        
        temp=head;
        head = head->next;
        free(temp);
    }
  
}
int main(void)
{
   int t,n,m,i,x;
   cin>>t;
   while(t--)
   {
	   struct node* temp,*head;
	    cin>>n;
	    cin>>x;
	    head=newNode(x);
	    temp=head;
	    for(i=0;i<n-1;i++)
	    {
			cin>>x;
			temp->next=newNode(x);
			temp=temp->next;
			}
	   
		reorderList(head);
	    printList(head);
freeList(head);
   }
   return 0;
}


/* Following is the Linked list node structure */
/*struct node
{
    int data;
    struct node* next;
};*/

#include <cassert>

namespace {
    node* split(node* head) // returns head of second sublist
    {
        node* prev {nullptr};
        
        for (auto fast = head; fast != nullptr && fast->next != nullptr;
                               fast = fast->next->next) {
            prev = head;
            head = head->next;
        }
        
        if (prev != nullptr) prev->next = nullptr;
        return head;
    }
    
    inline void rev_step(node*& acc, node*& cur)
    {
        const auto head = cur;
        cur = cur->next;
        head->next = acc;
        acc = head;
    }
    
    node* rev(node* acc, node* cur)
    {
        while (cur != nullptr) rev_step(acc, cur);
        return acc;
    }
    
    inline node* reverse(node* const head)
    {
        return rev(nullptr, head);
    }
    
    node* interleave(node* fst, node* snd)
    {
        if (fst == nullptr) return snd;
        if (snd == nullptr) return fst;
        
        const auto head = fst;
        
        while (fst->next != nullptr && snd->next != nullptr) {
            const auto snd_next = snd->next;
            snd->next = fst->next;
            fst->next = snd;
            fst = snd->next;
            snd = snd_next;
        }
        
        if (snd->next == nullptr) snd->next = fst->next;
        fst->next = snd;
        
        return head;
    }
}

void reorderList(node* const head) 
{
    if (head == nullptr || head->next == nullptr) return;

    const auto new_head = interleave(head, reverse(split(head)));
    assert(new_head == head);
}
