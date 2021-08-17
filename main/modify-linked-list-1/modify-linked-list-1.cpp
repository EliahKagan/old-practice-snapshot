/*Complete the function below
Node is as follows:
struct Node
{
    int data;
    struct Node* next;
};
*/
struct Node* modifyTheList(struct Node* const head)
{
    deque<struct Node*> nodes;
    for (auto cur = head; cur != nullptr; cur = cur->next)
        nodes.push_back(cur);
    
    while (nodes.size() > 1u) { // front and back exist and are distinct
        nodes.front()->data -= nodes.back()->data;
        nodes.pop_front();
        nodes.pop_back();
    }
    
    return head;
}
