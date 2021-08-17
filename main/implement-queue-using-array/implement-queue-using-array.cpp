/* 

The structure of the class is
class Queue {
private:
    int arr[10001];
    int front;
    int rear;

public :
    Queue(){front=0;rear=0;}
    void push(int);
    int pop();
};
 */

template<typename T, size_t N>
constexpr size_t lengthof(const T(&)[N]) { return N; }

/* The method push to push element into the queue */
void Queue::push(const int x)
{
    assert(rear != lengthof(arr));
    arr[rear++] = x;
}

/*The method pop which return the element poped out of the queue*/
int Queue::pop()
{
    constexpr auto no_element = -1;
    return front == rear ? no_element : arr[front++];
}

