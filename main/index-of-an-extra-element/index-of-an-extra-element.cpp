/*Complete the function below*/
int findExtra(int a[],int b[],int n)
{
    auto i = 0;
    while (a[i] == b[i]) ++i;
    return i;
}
