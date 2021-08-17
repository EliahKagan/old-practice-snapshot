/* 
The structure of the node of the queue is
struct QueueNode
{
    int data;
    QueueNode *next;
};


and the structure of the class is
class Queue {
private:
    QueueNode *front;
    QueueNode *rear;
public :
    void push(int);
    int pop();
};

 */

/* The method push to push element into the queue*/
void Queue::push(const int x)
{
    const auto node = new QueueNode{x, nullptr};
    
    if (rear == nullptr) {
        assert(front == nullptr);
        front = rear = node;
    } else {
        assert(rear->next == nullptr);
        rear->next = node;
        rear = node;
    }
}

/*The method pop which return the element poped out of the queue*/
int Queue::pop()
{
    constexpr auto no_element = -1;
    
    if (front == nullptr) {
        assert(rear == nullptr);
        return no_element;
    }
    
    assert(rear != nullptr);
    
    const auto popped = front;
    if ((front = popped->next) == nullptr) rear = nullptr;
    
    const auto ret = popped->data;
    delete popped;
    return ret;
}
