class GfG
{
        /*You are required to complete this function */
	int remove_duplicate(final int[] a)
	{
	    if (a.length == 0) return 0;
	    
	    int i = 0;
	    for (int j = 1; j != a.length; ++j)
	        if (a[i] != a[j]) a[++i] = a[j];
	    
	    return ++i;
	}
}
