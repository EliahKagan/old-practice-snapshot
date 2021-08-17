/*You are required to complete this method */
int countValues(const int n) // brute force method
{
    int count = 0;
    
    const int istop = n + 1;
    for (int i = 0; i != istop; ++i)
        if (n + i == (n ^ i)) ++count;
    
    return count;
}
