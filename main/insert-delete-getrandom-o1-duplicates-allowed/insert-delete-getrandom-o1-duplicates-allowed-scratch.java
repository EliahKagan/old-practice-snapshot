import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ThreadLocalRandom;

final class RandomizedCollection {
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    public boolean insert(final Integer val) {
        // Find or create this value's row in the index-tracking table.
        final Set<Integer> valIndices =
                _indexTable.computeIfAbsent(val, key -> new HashSet<>());

        // Append the value, record its index, and report if it is unique.
        final boolean ret = valIndices.isEmpty();
        valIndices.add(_elems.size());
        _elems.add(val);
        return ret;
    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    public boolean remove(final Integer val) {
        // Check if we have the value, and report if we do not.
        final Set<Integer> valIndices =
                _indexTable.getOrDefault(val, Collections.emptySet());
        if (valIndices.isEmpty()) return false;

        // Find and remove some index to an occurrence of the value.
        final int valIndex = valIndices.iterator().next();
        valIndices.remove(valIndex);

        // If the element we wish to remove is not the back element...
        final int otherIndex = _elems.size() - 1;
        if (valIndex != otherIndex) {
            // ...then copy the back element to the newly vacated position.
            final Integer other = _elems.get(otherIndex);
            _elems.set(valIndex, other);

            // ...and update the index-tracking table accordingly.
            final Set<Integer> otherIndices = _indexTable.get(other);
            otherIndices.remove(otherIndex);
            otherIndices.add(valIndex);
        }

        // Pop off the back element.
        _elems.remove(otherIndex);
        return true;
    }

    /** Get a random element from the collection. */
    public int getRandom() {
        return _elems.get(ThreadLocalRandom.current().nextInt(_elems.size()));
    }

    private final List<Integer> _elems = new ArrayList<>();

    private final Map<Integer, Set<Integer>> _indexTable = new HashMap<>();
}

final class UnitTest {
    public static void main(final String[] args) {
        final RandomizedCollection rc = new RandomizedCollection();

        final class Tester {
            private void insert(final int val) {
                System.out.println(rc.insert(val));
            }

            private void remove(final int val) {
                System.out.println(rc.remove(val));
            }
        }

        final Tester test = new Tester();

         System.out.println("INSERTIONS:");
         test.insert(4);
         test.insert(3);
         test.insert(4);
         test.insert(2);
         test.insert(4);

         System.out.println();

         System.out.println("REMOVALS:");
         test.remove(4);
         test.remove(3);
         test.remove(4);
         test.remove(4);
         test.remove(3);
    }

    private UnitTest() { throw new AssertionError(); }
}
