/*
  Rotate a linked list after node k
  The input list will have at least one element  
  A Linked List node has following structure.
  struct node
  {
     int data;
     struct node *next;
  }
*/

#include <assert.h>

static struct node *advance(struct node *head, int count)
{
    assert(count >= 0);
    
    for (; count != 0; --count) {
        assert(head != NULL);
        head = head->next;
    }
    
    return head;
}

static struct node *split(struct node *const head, const int k)
{
    assert(k > 0);
    
    struct node *const prev = advance(head, k - 1), *const cur = prev->next;
    prev->next = NULL;
    return cur;
}

static struct node *join(struct node *const left, struct node *const right)
{
    if (left == NULL) return right;
    
    struct node *cur = left;
    while (cur->next != NULL) cur = cur->next;
    cur->next = right;
    
    return left;
}

/*  **head_ref is a pointer to head pointer.  This function
    should modify value at head_ref to change head (if required)*/
void rotate(struct node **head_ref, const int k)
{
    assert(head_ref != NULL && k >= 0);
    
    struct node *const right = *head_ref;
    if (k == 0 || right == NULL) return;
    
    struct node *const left = split(right, k);
    *head_ref = join(left, right);
}
