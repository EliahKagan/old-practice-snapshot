#include <iostream> //#include<bits/stdc++.h>
using namespace std;

struct StackNode
{
    int data;
    StackNode *next;
};

class Stack {
private:
StackNode *top;
public :
    
    void push(int);
    int pop();
};


int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        Stack *sq = new Stack();

        int Q;
        cin>>Q;
        while(Q--){
        int QueryType=0;
        cin>>QueryType;
        if(QueryType==1)
        {
            int a;
            cin>>a;
            sq->push(a);
        }else if(QueryType==2){
            cout<<sq->pop()<<" ";

        }
        }
        cout<<endl;
    }
    }


/* 
The structure of the node of the stack is
struct StackNode
{
    int data;
    StackNode *next;
};

and the structure of the class is
class Stack {
private:
  StackNode *top;
public :
    void push(int);
    int pop();
};
 */

/* The method push to push element into the stack */
void Stack::push(const int x)
{
    top = new StackNode{x, top};
}

/*The method pop which return the element poped out of the stack*/
int Stack::pop()
{
    constexpr auto no_element = -1;
    
    if (top == nullptr) return no_element;
    
    const auto oldtop = top;
    const auto x = oldtop->data;
    
    top = top->next;
    delete oldtop;
    
    return x;
}
