/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*Complete the function below*/
class GfG
{
	int find(final int[] a, int x)
	{
	    // Follow the path to the representative (ancestor).
	    int r = x;
	    while (r != a[r]) r = a[r];

	    // Compress the path.
	    while (x != r) {
	        final int p = a[x];
	        a[x] = r;
	        x = p;
	    }

	    return r;
	}

	void unionSet(final int[] a, final int x, final int z)
	{
	    a[find(a, x)] = a[find(a, z)];
	}
}
