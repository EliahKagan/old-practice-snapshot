/* Print the nth node of the linked list
   Node is defined as 
struct node
{
    int data;
    struct node* next;
};*/

#include <assert.h>

// Should return data of node at given index. The function may
//  assume that there are at least index+1 nodes in linked list 
int GetNth(struct node* const head, const int index)
{
    assert(head != NULL && index >= 0);
    return index == 0 ? head->data : GetNth(head->next, index - 1);
}

