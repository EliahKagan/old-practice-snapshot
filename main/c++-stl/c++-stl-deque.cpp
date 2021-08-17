/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for C++
/*You are required to complete below methods*/
/*prints space separated
elements of the deque A*/
void print(deque<int> &A)
{
    if (A.empty()) cout << "-1\n";
    else {
        for (const auto x : A) cout << x << ' ';
        cout << '\n';
    }
}
/*inserts an element x at
the front of the deque A*/
void add_in_front(deque<int> &A, const int x)
{
    A.push_front(x);
}
/*inserts an element x at
the back of the deque A */
void add_in_back(deque<int> &A, const int x)
{
    A.push_back(x);
}
/*remove element from
back of the deque A*/
void remove_from_back(deque<int> &A)
{
    A.pop_back();
}
/*remove element from
front of the deque A*/
void remove_from_front(deque<int> &A)
{
    A.pop_front();
}
/*sort the the deque A in ascending order*/
void sort(deque<int> &A)
{
    sort(begin(A), end(A));
}
/*reverses the deque A*/
void reverse(deque<int> &A)
{
    reverse(begin(A), end(A));
}
/*returns the size of the deque  A */
int size(deque<int> &A)
{
    return A.size();
}
/* returns element at front
of the deque*/
int element_at_front(deque<int> &A)
{
    return A.front();
}
/*returns element at end
of the deque*/
int element_at_back(deque<int> &A)
{
    return A.back();
}
