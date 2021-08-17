/*
delete n nodes after m nodes
  The input list will have at least one element  
  Node is defined as 
  struct node
  {
     int data;
     struct node *next;
  }

*/

#include <assert.h>

void linkdelete(struct node *head, const int m, const int n)
{
    assert(m > 0 && n >= 0);
    
    for (struct node sentinel = { -1, head }, *cur = &sentinel; ; ) {
        for (int i = m; i != 0; --i) {
            if (cur->next == NULL) return;
            cur = cur->next;
        }
        
        for (int i = n; i != 0; --i) {
            struct node *const next = cur->next;
            if (next == NULL) return;
            cur->next = next->next;
            free(next);
        }
    }
}
