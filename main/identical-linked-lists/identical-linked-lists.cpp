/*
Structure of the node of the linked list is as
struct Node
{
	int data;
	struct Node *next;
};
*/
// Complete this function
// return true if two list are identical else return false
bool areIdentical(struct Node *head1, struct Node *head2)
{
    while (head1 != nullptr && head2 != nullptr) {
        if (head1->data != head2->data) return false;
        
        head1 = head1->next;
        head2 = head2->next;
    }
    
    return head1 == nullptr && head2 == nullptr;
}
