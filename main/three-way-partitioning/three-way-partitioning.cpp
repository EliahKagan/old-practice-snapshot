/*The function should return the modified array
as specified in the problem statement */
vector<int> threeWayPartition(vector<int> a, const int lowVal,
                                             const int highVal)
{
    const auto p = partition(begin(a), end(a), [lowVal](const int x) { 
        return x < lowVal;
    });
    
    partition(p, end(a), [highVal](const int x) {
        return x <= highVal;
    });
    
    return a;
}
