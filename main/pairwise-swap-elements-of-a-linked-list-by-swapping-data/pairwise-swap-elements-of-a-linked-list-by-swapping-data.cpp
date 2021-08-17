/*
  Pairwise swap a linked list
  The input list will have at least one element  
  node is defined as 
  struct node
  {
     int data;
     struct node *next;
  }
*/
static inline void iswap(int *const p, int *const q)
{
    const int tmp = *p;
    *p = *q;
    *q = tmp;
}

void pairWiseSwap(struct node *head)
{
    for (; head != NULL && head->next != NULL; head = head->next->next)
        iswap(&head->data, &head->next->data);
}
