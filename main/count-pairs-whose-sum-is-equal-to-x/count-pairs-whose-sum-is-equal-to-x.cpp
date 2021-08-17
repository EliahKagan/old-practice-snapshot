/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/*
Structure of the node of the linked list is as
struct Node
{
   int data;
   struct Node* next;
};
*/
// your task is to complete this function
int countPairs(struct Node* head1, struct Node* head2, int x)
{
    unordered_set<int> complements;
    for (; head1; head1 = head1->next)
        complements.insert(x - head1->data);

    auto count = 0;
    for (; head2; head2 = head2->next)
        count += complements.count(head2->data);

    return count;
}
