#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<stdlib.h>

/* Link list node */
struct node
{
    int data;
    struct node* next;
};

struct node *start = NULL;

void sortList(struct node *head);

// Function to sort a linked list of 0s, 1s and 2s
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
void insert(int n1)
{
    int n,value,i;
    //scanf("%d",&n);
    n=n1;
    struct node *temp {}; // note: not initialized in GfG code
    for(i=0;i<n;i++)
    {
        scanf("%d",&value);
        
        if(i==0)
        {
            start=(struct node *) malloc( sizeof(struct node) );
            start->data=value;
            start->next=NULL;
            temp=start;
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

int main()
{
    
    int n;
    
    int t;
    scanf("%d",&t);
    
    while (t--) {
        scanf("%d",&n);
        
        insert(n);
        sortList(start);
        printList(start);
    }
    
    return 0;
}


/*
  Sort the list of 0's,1's and 2's
  The input list will have at least one element  
  Node is defined as 
  struct node
  {
     int data;
     struct node *next;
  }

*/

#include <vector>

void sortList(node *head)
{
    constexpr auto stop = 3;
    
    using Index = std::vector<int>::size_type;
    std::vector<int> counts (static_cast<Index>(stop));
    
    for (auto cur = head; cur != nullptr; cur = cur->next) {
        ++counts.at(static_cast<Index>(cur->data));
    }
    
    for (auto data = 0; data != stop; ++data) {
        for (auto i = counts[static_cast<Index>(data)]; i != 0; --i) {
            head->data = data;
            head = head->next;
        }
    }
}
