/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//function Template for C++
queue<long long int> rev(queue<long long int> q)
{
    stack<long long int> s;
    for (; !q.empty(); q.pop()) s.push(q.front());
    for (; !s.empty(); s.pop()) q.push(s.top());
    return q;
}
