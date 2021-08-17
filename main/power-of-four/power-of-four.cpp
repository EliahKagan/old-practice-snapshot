int isPowerOfFour(unsigned int n)
{
    while (n % 4u == 0u) n /= 4u;
    return n == 1u;
}
