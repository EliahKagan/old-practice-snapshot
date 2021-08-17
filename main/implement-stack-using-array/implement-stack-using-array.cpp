/* 

The structure of the class is
class Stack
{
private:
    int arr[1000];
    int top;
public:
    Stack(){top=-1;}
    int pop();
    void push(int);
};

 */

template<typename T, size_t N>
constexpr int maxindexof(const T(&)[N])
{
    return static_cast<int>(N) - 1;
}

/* The method push to push element into the stack */
void Stack::push(const int x)
{
    assert(top < maxindexof(arr));
    arr[++top] = x;
}

/*The method pop which return the element poped out of the stack*/
int Stack::pop()
{
    constexpr int no_element = -1;
    return top < 0 ? no_element : arr[top--];
}
