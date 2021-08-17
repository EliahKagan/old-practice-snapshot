import java.util.Arrays;
import java.util.Scanner;
class Operating{
	public static void main(String[] args){
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt();
		while(t-->0){
			int n=sc.nextInt();
			int[] a=new int[10000];
			Arrays.fill(a,-1);
			for(int i=0;i<n;i++){
				a[i]=sc.nextInt();
			}
			int x = sc.nextInt();
			int y = sc.nextInt();
			int yi = sc.nextInt();
			int z = sc.nextInt();
			GfG g = new GfG();
			boolean b = g.searchEle(a,x);
			if(b==true)
				System.out.print("1 ");
			else
				System.out.print("0 ");
			b = g.insertEle(a,y,yi);
			if(b){
			if(a[yi]==y)
				System.out.print("1 ");
			else
				System.out.print("0 ");
			}
			else
				System.out.print("0 ");
			b = g.deleteEle(a,z);
			if(b){
			if(!g.searchEle(a,z))
				System.out.println("1 ");
			else
				System.out.println("0 ");
			}
			else
				System.out.println("0 ");
		}
	}
}

/*Complete the function(s) below*/
class GfG
{
    private static boolean DEBUG = true;
    private static final int NO_ELEMENT = -1;

	public boolean searchEle(final int[] a, final int x)
	{
	    if (DEBUG) System.err.format("%nDEBUG: searchEle: x=%d%n", x);
	    if (x == NO_ELEMENT) throw new IllegalArgumentException();

	    for (final int y : a) {
	        if (y == -1) break;
	        if (y == x) return true;
	    }

        return false;
	}

	public boolean insertEle(final int a[], final int y, final int yi)
    {
        if (DEBUG) System.err.format("%nDEBUG: insertEle: y=%d, yi=%d%n", y, yi);
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
    {   // note: the problem checker seems to want this to always return true
        if (DEBUG) System.err.format("%nDEBUG: deleteEle: z=%d%n", z);
        if (z == NO_ELEMENT) throw new IllegalArgumentException();

        // move right until we find z, if it is present
        int i = 0;
        while (i != a.length && a[i] != NO_ELEMENT && a[i] != z) ++i;
        if (i == a.length || a[i] == NO_ELEMENT) return false;

        // shift elements one position leftward to cover deletion
        final int max_last = a.length - 1;
        for (; i != max_last && a[i + 1] != NO_ELEMENT; ++i) a[i] = a[i + 1];
        a[i] = NO_ELEMENT;
        return true;
	}
}
