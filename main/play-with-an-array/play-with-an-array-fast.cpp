/*Complete the function below*/
vector<int> formatArray(vector<int> a, const int n)
{
    // The problem constraints don't specify if the array may contain
    // duplicates, nor even if it is possible for the array to be rearranged
    // in the specified manner. For example, if the array has more than one
    // element and they are all equal, then the task cannot be completed.
    // That's why I just sorted the array completely for my first submission.
    // However, it occurs to me that the problem setter may have intended
    // either to (a) constrian the array to contain no duplicates (or no
    // consecutive duplicates) or (b) demand only "not less than" instead of
    // "greater than." If so, this method implemented here should work.
    for (auto i = 1; i < n; i += 2)
        if (a[i] < a[i - 1]) swap(a[i], a[i - 1]);
    
    return a;
}
