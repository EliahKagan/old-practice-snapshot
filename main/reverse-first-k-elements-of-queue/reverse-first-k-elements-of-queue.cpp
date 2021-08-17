/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for C++
queue<ll> modifyQueue(queue<ll> q, int k)
{
    assert(0 <= k && k <= q.size());
    stack<ll> s;
    for (; k-- != 0; q.pop()) s.push(q.front());

    queue<ll> ret;
    for (; !s.empty(); s.pop()) ret.push(s.top());
    for (; !q.empty(); q.pop()) ret.push(q.front());
    return ret;
}
