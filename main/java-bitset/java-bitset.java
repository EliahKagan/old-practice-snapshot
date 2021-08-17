import java.util.*;

final class Solution {
    // Returns an array of two newly created, zeroed-out bitsets of width n.
    private static BitSet[] createBitSets(final int n)
    {
        return new BitSet[] { null, new BitSet(n), new BitSet(n) };
    }
    
    private static void doOperation(final BitSet[] bitsets, final Scanner sc)
    {
        final String op = sc.next();
        final int fst = sc.nextInt(), snd = sc.nextInt();
        
        switch (op) {
            case "AND":     bitsets[fst].and(bitsets[snd]);     break;
            case "OR":      bitsets[fst].or(bitsets[snd]);      break;
            case "XOR":     bitsets[fst].xor(bitsets[snd]);     break;
            case "FLIP":    bitsets[fst].flip(snd);             break;
            case "SET":     bitsets[fst].set(snd);              break;
            default:        throw new UnsupportedOperationException();
        }
    }
    
    private static void printCardinalities(final BitSet[] bitsets)
    {
        System.out.format("%d %d%n", bitsets[1].cardinality(),
                                     bitsets[2].cardinality());
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            final BitSet[] bitsets = createBitSets(sc.nextInt());
            
            for (int m = sc.nextInt(); m > 0; --m) {
                doOperation(bitsets, sc);
                printCardinalities(bitsets);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
