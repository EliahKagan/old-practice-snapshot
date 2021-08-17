import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

final class MyPair<T> {
    public final T first, second;
    
    public MyPair()
    {
        first = second = null;
    }
    
    public MyPair(final T fst, final T snd)
    {
        first = fst;
        second = snd;
    }

    @Override
    public boolean equals(Object obj) { // FIXME: refactor this
        if (this == obj) return true;
        if (null == obj) return false;
        
        
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final MyPair<?> other = (MyPair<?>) obj;
        if (!Objects.equals(this.first, other.first)) {
            return false;
        }
        if (!Objects.equals(this.second, other.second)) {
            return false;
        }
        return true;
    }
    
    @Override
    public int hashCode()
    {
        return first.hashCode() ^ second.hashCode() * HASHING_MULTIPLIER;
    }
    
    // See rationale at https://stackoverflow.com/a/2816747 by
    // https://stackoverflow.com/users/21499/dr-hans-peter-störr. Note that
    // this is a somewhat different use case because the values being
    // multiplied here are themselves hash codes, possibly generated in a
    // similar way. If this yields more hash collisions than expected, blame
    // me, not him!
    private static final int HASHING_MULTIPLIER = 92_821;
}

final class UnitTest {
    public static void main(final String[] args)
    {
        final int r = 1000; // Manhattan metric
        
        final Set<MyPair<Integer>> pairs = new HashSet<>();
        final Set<Integer> codes = new HashSet<>();
        
        for (int i = -r; i <= r; ++i) {
            for (int j = -r; j <= r; ++j) {
                MyPair<Integer> ij = new MyPair<>(i, j);
                pairs.add(ij);
                codes.add(ij.hashCode());
            }
        }
        
        final int npairs = pairs.size(), ncodes = codes.size();
        final double mean_pairs_per_code = (double)npairs / (double)ncodes;
        
        System.out.format("pairs.size() = %d%n", npairs);
        System.out.format("codes.size() = %d%n", ncodes);
        
        System.out.format("On average (NOT what matters most) ~%.3f values "
                            + "share a code.%n", mean_pairs_per_code);
    }
    
    private UnitTest() { } // don't instantiate this class
}
