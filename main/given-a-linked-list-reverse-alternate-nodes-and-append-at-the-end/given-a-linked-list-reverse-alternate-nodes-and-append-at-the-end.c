/*
  reverse alternate nodes and append at the end
  The input list will have at least one element  
  Node is defined as 
  struct node
  {
     int data;
     struct node *next;
  }

*/

#include <assert.h>

void rearrange(struct node *odd)
{
    assert(odd != NULL);
    struct node *even = NULL;
    
    while (odd->next != NULL) {
        struct node *const next = odd->next->next;
        odd->next->next = even;
        even = odd->next;
        odd->next = next;
        if (odd->next != NULL) odd = odd->next;
    }
    
    odd->next = even;
}
