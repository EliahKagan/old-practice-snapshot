static int gcd(const int m, const int n)
{
    return n == 0 ? m : gcd(n, m % n);
}

/*You are required to complete this function*/
void addFraction(int num1, int den1, int num2, int den2)
{
    const int numq = num1 * den2 + num2 * den1, denq = den1 * den2;
    const int d = gcd(numq, denq);
    cout << numq / d << '/' << denq / d << '\n';
}
