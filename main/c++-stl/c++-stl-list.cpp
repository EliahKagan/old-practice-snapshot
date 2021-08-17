/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for C++
/*You are required to complete below methods*/
/*prints space separated
elements of list A*/
void print(list<int> &A)
{
    if (A.empty()) {
        cout << "-1\n";
    } else  {
        for (const auto x : A) cout << x << ' ';
        cout << '\n';
    }
}
/*remove element from
back of list A*/
void remove_from_back(list<int> &A)
{
    A.pop_back();
}
/*remove element from
front of list A*/
void remove_from_front(list<int> &A)
{
    A.pop_front();
}
/*inserts an element x at
the back of the list A */
void add_to_list(list<int> &A, const int x)
{
    A.push_back(x);
}
/*sort the list A in ascending order*/
void sort_list(list<int> &A)
{
    A.sort();
}
/*reverses the list A*/
void reverse_list(list<int> &A)
{
    A.reverse();
}
/*returns the size of the list  A */
int size_of_list(list<int> &A)
{
    return A.size();
}
/*inserts an element x at
the front of the list A*/
void add_from_front(list<int> &A, const int x)
{
    A.push_front(x);
}
