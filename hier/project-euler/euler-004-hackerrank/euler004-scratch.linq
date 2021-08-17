<Query Kind="Program" />

private static bool SixDigitNumberIsPalindrome(int n) // assumes 6-digit n
{
    const int b = 10;

    var ones = n % b;
    if (ones == 0) return false;

    var tens = (n /= b) % b;
    
    var hundreds = (n /= b) % b;

    return (n /= b) % b == hundreds && (n /= b) % b == tens
                                    && (n / b) % b == ones;
}

private static IEnumerable<int> FindSixDigitPalindromes()
{
    for (var i = 100000; i != 1000000; ++i)
        if (SixDigitNumberIsPalindrome(i)) yield return i;
}

private static void Main()
{
    FindSixDigitPalindromes().Dump();
}