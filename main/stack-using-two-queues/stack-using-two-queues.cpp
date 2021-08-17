/* The structure of the class is
class QueueStack{
private:
    queue<int> q1;
    queue<int> q2;
public:
    void push(int);
    int pop();
};
 */

// See http://cstheory.stackexchange.com/a/2589 for algorithm details
// (author: http://cstheory.stackexchange.com/users/988/alex-ten-brink).

/* The method push to push element into the stack */
void QueueStack::push(const int x)
{
    q1.push(x);
    
    const auto n1 = q1.size();
    
    for (auto i = n1; --i != 0; ) {
        const auto y = q1.front();
        q1.pop();
        q1.push(y);
    }
    
    auto n2 = q2.size();
    
    if (n1 * n1 > n2) {
        for (; n2 != 0u; --n2) {
            q1.push(q2.front());
            q2.pop();
        }
        
        swap(q1, q2);
    }
}

/*The method pop which return the element poped out of the stack*/
int QueueStack::pop()
{
    constexpr auto no_element = -1;
    
    if (!q1.empty()) {
        const auto x = q1.front();
        q1.pop();
        return x;
    }
    
    if (!q2.empty()) {
        const auto x = q2.front();
        q2.pop();
        return x;
    }
    
    return no_element;
}
