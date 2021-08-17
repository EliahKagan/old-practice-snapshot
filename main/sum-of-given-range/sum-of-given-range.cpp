/*Complete the function below*/
int getSum(int *const arr, const int n, int a, int b)
{
    auto acc = 0;
    for (b = min(b, n - 1); a <= b; ++a) acc += arr[a];
    return acc;
}
