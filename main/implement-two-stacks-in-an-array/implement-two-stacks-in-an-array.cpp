/*The structure of the class is
class twoStacks
{
    int *arr;
    int size;
    int top1, top2;
public:
   twoStacks(int n=100){size = n; arr = new int[n]; top1 = -1; top2 = size;}
 
   void push1(int x);
   void push2(int x);
   int pop1();
   int pop2();
};
*/

constexpr int no_element {-1};

/* The method push to push element into the stack 1 */
void twoStacks::push1(const int x)
{
    assert(top2 - top1 > 1);
    arr[++top1] = x;
}
   
/* The method push to push element into the stack 2*/
void twoStacks::push2(const int x)
{
    assert(top2 - top1 > 1);
    arr[--top2] = x;
}
   
/* The method pop to pop element from the stack 1 */
int twoStacks::pop1()
{
    return top1 == -1 ? no_element : arr[top1--];
}

/* The method pop to pop element from the stack 2 */
int twoStacks::pop2()
{
    return top2 == size ? no_element : arr[top2++];
}
