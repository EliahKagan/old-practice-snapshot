/*Structure of the node of the linled list is as
struct Node {
	int data;
	struct Node* next;
};*/
// your task is to complete this function 
// function should return sum of last n nodes
int sumOfLastN_Nodes(struct Node* head, int n)
{
    assert(n >= 0);
    
    // make a gap of exactly n nodes from head to tail
    auto tail = head;
    for (; n != 0 && tail != nullptr; --n) tail = tail->next;
    if (n != 0) return 0;
    
    // advance the gap to the end of the list
    for (; tail != nullptr; tail = tail->next) head = head->next;
    
    // head is now the head of the size-n trailing sublist - sum that list
    auto acc = 0;
    for (; head != nullptr; head = head->next) acc += head->data;
    return acc;
}
