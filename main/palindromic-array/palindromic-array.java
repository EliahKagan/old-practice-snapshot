/*Complete the Function below*/
class GfG
{
    private static boolean isPalindrome(final String s)
    {
        for (int i = 0, j = s.length(); i < --j; ++i)
            if (s.charAt(i) != s.charAt(j)) return false;
        
        return true;
    }
    
	public int palinArray(final int[] a, final int n)
	{
	    for (int i = 0; i != n; ++i)
	        if (!isPalindrome(String.valueOf(a[i]))) return 0;
	    
	    return  1;
	}
}
