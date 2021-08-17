/*
  Print elements of a linked list on console 
  head pointer input could be NULL as well for empty list
  Node is defined as 
  struct Node
  {
     int data;
     struct Node *next;
  }
*/
void display(struct Node *const head)
{
    if (head != NULL) {
        printf("%d ", head->data);
        display(head->next);
    }
}

