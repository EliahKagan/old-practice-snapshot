/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//User function Template for C++
// your task is to complete the function
// function should return true/false or 1/0
bool pairWiseConsecutive(stack<int> s)
{
    // The s parameter is passed by value, so the caller copies or moves the
    // entire stack. Therefore, no matter what this function does to its local
    // copy, the caller's copy cannot be further affected. So it is unnecessary
    // (and pointless) to push elements back onto s before returning.
    if (s.size() % 2u != 0u) s.pop();

    while (!s.empty()) {
        const auto x = s.top();
        s.pop();
        const auto y = s.top();
        s.pop();

        if (abs(x - y) != 1) return false;
    }

    return true;
}
