/*Complete the function below*/
final class GfG
{
    private static BigInteger factorial(long n)
    {
        BigInteger acc = BigInteger.ONE;
        for (; n > 1; --n) acc = acc.multiply(BigInteger.valueOf(n));
        return acc;
    }
    
	long findSumofDigits(long n)
	{
	    final String repr = factorial(n).toString();
	    
	    long acc = 0;
	    for (int i = 0; i != repr.length(); ++i)
	        acc += repr.charAt(i) - '0';
	    
	    return acc;
	}
}
