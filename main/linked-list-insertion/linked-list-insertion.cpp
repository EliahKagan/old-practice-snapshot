/*
Structure of the linked list node is as
struct node
{
    int data;
    struct node *next;
};
*/

// function inserts the data in front of the list
void insertAtBegining(struct node** headRef, int newData)
{
    *headRef = new node{newData, *headRef};
}

// function appends the data at the end of the list
void insertAtEnd(struct node** headRef, int newData)
{
    if (*headRef == nullptr) {
        *headRef = new node{newData, nullptr};
        return;
    }
    
    auto p = *headRef;
    while (p->next != nullptr) p = p->next;
    p->next = new node{newData, nullptr};
}
