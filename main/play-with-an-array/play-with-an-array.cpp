/*Complete the function below*/
vector<int> formatArray(vector<int> a, int n)
{
    // Simply sorting the array completely satisfies the requirements here,
    // and is pretty fast (std::sort has strict time complexity requirements;
    // see https://en.wikipedia.org/wiki/Introsort, invented for std::sort).
    sort(begin(a), begin(a) + n);
    return a;
}
