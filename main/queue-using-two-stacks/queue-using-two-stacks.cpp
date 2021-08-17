/* The structure of the class is
class StackQueue{
private:   
    // These are STL stacks ( http://goo.gl/LxlRZQ )
    stack<int> s1;
    stack<int> s2;
public:
    void push(int);
    int pop();
}; */

/* The method push to push element into the queue */
void StackQueue::push(const int x)
{
    s1.push(x);
}

/*The method pop which return the element poped out of the queue*/
int StackQueue::pop()
{
    constexpr auto no_element = -1;
    
    // Recharge s2 from s1, if necessary.
    if (s2.empty()) {
        if (s1.empty()) return no_element;
        
        do {
            s2.push(s1.top());
            s1.pop();
        }
        while (!s1.empty());
    }
    
    // Pop from s2.
    const auto ret = s2.top();
    s2.pop();
    return ret;
}
