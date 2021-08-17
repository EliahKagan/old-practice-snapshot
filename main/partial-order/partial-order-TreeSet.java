import java.util.Set;
import java.util.TreeSet;

/** A tagged integer whose tag affects equality comparisons but not ordering.
 * Note: this class has a natural ordering that is inconsistent with equals. */
final class TaggedInt implements Comparable<TaggedInt> {
    public TaggedInt(final int value) {  Value = value; }

    public boolean equals(final TaggedInt other) {
        return Value == other.Value && Tag == other.Tag;
    }

    @Override
    public boolean equals(final Object other) {
        return other instanceof TaggedInt && equals((TaggedInt)other);
    }

    @Override
    public int hashCode() { return Value; }

    @Override
    public int compareTo(final TaggedInt other) { return Value - other.Value; }

    @Override
    public String toString() { return String.format("%d[%d]", Value, Tag); }

    public final int Value;
    public final int Tag = NextTag++;

    private static int NextTag = 0;
}

final class UnitTest {
    public static void main(final String[] args) {
         final TaggedInt i = new TaggedInt(5);
         final TaggedInt j = new TaggedInt(3);
         final TaggedInt k = new TaggedInt(5);

         System.out.format("%s %s %s%n",
                           i.equals(j), i.equals(k), j.equals(k));

         System.out.format("%s %s %s%n%n", i, j, k);

         final Set<TaggedInt> s = new TreeSet<>();
         s.add(i);
         s.add(j);
         s.add(k);

         for (final TaggedInt e : s) System.out.println(e);
    }

    private UnitTest() { throw new AssertionError(); }
}
