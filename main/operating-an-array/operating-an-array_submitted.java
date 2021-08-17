/*Complete the function(s) below*/
class GfG
{
    private static boolean DEBUG = false;
    private static final int NO_ELEMENT = -1;
    
	public boolean searchEle(final int[] a, final int x)
	{
	    if (DEBUG) System.err.format("DEBUG: searchEle: x=%d%n", x);
	    if (x == NO_ELEMENT) throw new IllegalArgumentException();
	    
	    for (final int y : a) {
	        if (y == -1) break;
	        if (y == x) return true;
	    }
        
        return false;
	}
	
	public boolean insertEle(final int a[], final int y, final int yi)
    {
        if (DEBUG) System.err.format("DEBUG: insertEle: y=%d, yi=%d%n", y, yi);
        if (y == NO_ELEMENT) throw new IllegalArgumentException();
        
        int j = a.length - 1;
        
        if (yi < 0 || yi > j || a[j] != NO_ELEMENT) return false;
        
        // move j to the leftmost nonelement
        while (j != yi && a[--j] == NO_ELEMENT) { }
        
        // shift elements one position rightward to make room for insertion
        for (; j != yi; --j) a[j] = a[j - 1];
        
        a[yi] = y;
        return true;
	}
	
	public boolean deleteEle(final int[] a, final int z)
    {
        if (DEBUG) System.err.format("DEBUG: deleteEle: z=%d%n", z);
        if (z == NO_ELEMENT) throw new IllegalArgumentException();
        
        // move right until we find z, if it is present
        int i = 0;
        while (i != a.length && a[i] != NO_ELEMENT && a[i] != z) ++i;
        if (i == a.length || a[i] == NO_ELEMENT) return true;
        
        // shift elements one position leftward to cover deletion
        final int max_last = a.length - 1;
        for (; i != max_last && a[i + 1] != NO_ELEMENT; ++i) a[i] = a[i + 1];
        a[i] = NO_ELEMENT;
        return true;
	}
}
