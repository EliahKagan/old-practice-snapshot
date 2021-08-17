import java.lang.Math;
import java.util.*;
class UniqueRows{
    public static void main(String[] args)
    {  Scanner sc=new Scanner(System.in);
        int t=sc.nextInt();
        while(t-->0){
            int r=sc.nextInt();
            int c=sc.nextInt();
            int[][] a=new int [r][c];
            for(int i=0;i<r;i++)
                for(int j=0;j<c;j++)
                    a[i][j]=sc.nextInt();
            GfG g=new GfG();
            g.printMat(a,r,c);
            System.out.println();
        }
    }
}

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/

final class BitTrie {
    /** Adds a chain to the trie. Returns true iff it wasn't already added. */
    boolean addChain(final int[] bits, int start, int end) {
        if (start >= end) throw new IllegalArgumentException("invalid range");

        BitTrie node = this;

        for (--end; start != end; ++start) {
            if (bits[start] == 0) {
                if (node._left == null) node._left = new BitTrie();
                node = node._left;
            } else {
                if (node._right == null) node._right = new BitTrie();
                node = node._right;
            }
        }

        if (bits[end] == 0) {
            if (node._left == null) {
                node._left = new BitTrie();
                return true;
            }
            else return false;
        } else {
            if (node._right == null) {
                node._right = new BitTrie();
                return true;
            }
            else return false;
        }
    }

    private BitTrie _left = null, _right = null;
}

/*Complete the given function*/
class GfG {
    public static void printMat(final int[][] a, final int r, final int c) {
        if (r <= 0 || c <= 0) throw new IllegalArgumentException("bad size");

        final BitTrie trie = new BitTrie();
        for (int i = 0; i != r; ++i)
            if (trie.addChain(a[i], 0, c)) printRow(a[i], c);
    }

    private static void printRow(final int[] row, final int end) {
        for (int j = 0; j != end; ++j) System.out.format("%d ", row[j]);
        System.out.print("$");
    }
}
