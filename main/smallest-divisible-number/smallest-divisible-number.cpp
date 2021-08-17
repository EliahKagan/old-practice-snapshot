constexpr long long gcd(const long long m, const long long n)
{
    return n == 0LL ? m : gcd(n, m % n);
}

constexpr long long lcm(const long long m, const long long n)
{
    return m / gcd(m, n) * n;
}

/*You are required to complete this method */
long long getSmallestDivNum(const long long n)
{
    auto acc = 1LL;
    for (auto k = 2LL; k <= n; ++k) acc = lcm(acc, k);
    return acc;
}
