/*structure of a node of the linked list is as
struct Node
{
	int data;
	struct Node* next;
};
*/
// Function should return 0 is length is even else return 1
int isLengthEvenOrOdd(struct Node* head)
{
    auto len = 0;
    for (; head != nullptr; head = head->next) ++len;
    return len % 2;
}
