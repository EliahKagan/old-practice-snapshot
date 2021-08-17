/*Complete the function below*/
int findExtra(int a[],int b[],int n)
{
    assert (n >= 0);
    
    auto i = 0;
    while (i != n && a[i] == b[i]) ++i;
    return i;
}
