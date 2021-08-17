/*The structure of linked list is the following
struct node
{
int data;
node* next; };*/
/*The function removes the loop from the linked list if present
You are required to complete this method*/
void removeTheLoop(node *head)
{
    if (head == nullptr) return;
    
    unordered_set<node *> nodes {head};
    while (head->next != nullptr && nodes.find(head->next) == nodes.end())
        nodes.insert(head = head->next);
    
    head->next = nullptr;
}
