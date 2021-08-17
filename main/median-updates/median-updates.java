import java.util.Scanner;
import java.util.TreeSet;

final class TaggedInt implements Comparable<TaggedInt> {
    TaggedInt(final int value) {
        tag = nextTag++;

        if (tag == Integer.MAX_VALUE)
            throw new IndexOutOfBoundsException("tag values exhausted!");

        this.value = value;
    }

    final int value, tag;

    @Override
    public int compareTo(final TaggedInt other) {
        final int byValue = Integer.compare(value, other.value);
        return byValue == 0 ? Integer.compare(tag, other.tag) : byValue;
    }

    private static int nextTag = Integer.MIN_VALUE;
}

final class Solution {
    private static int getSizeDelta(final TreeSet<TaggedInt> low,
                                    final TreeSet<TaggedInt> high) {
        return low.size() - high.size();
    }

    private static void complain() {
        System.out.println("Wrong!");
    }

    private static void printMedianOrComplain(final TreeSet<TaggedInt> low,
                                              final TreeSet<TaggedInt> high) {
        switch (getSizeDelta(low, high)) {
        case 0:
            if (low.isEmpty()) { // they're the same size, so high is empty too
                complain();
                break;
            }

            // Take the mean of the two medial elements. Converting them to
            // double before adding them instead of after prevents overflow.
            final double median = ((double)low.last().value
                                   + (double)high.first().value) / 2.0;

            final String format = (median == Math.floor(median) ? "%.0f%n"
                                                                : "%.1f%n");
            System.out.format(format, median);
            break;

        case +1:
            System.out.println(low.last().value); // low is the bigger set
            break;

        case -1:
            System.out.println(high.first().value); // high is the bigger set
            break;

        default:
            throw new AssertionError("the balancing invariant was violated!");
        }
    }

    private static void rebalance(final TreeSet<TaggedInt> low,
                                  final TreeSet<TaggedInt> high) {
        switch (getSizeDelta(low, high)) {
        case +2:
            high.add(low.pollLast()); // low is the bigger set
            break;

        case -2:
            low.add(high.pollFirst()); // high is the bigger set
            break;

        default:
            // Do nothing, because the sets cannot be made any more balanced.
        }
    }

    private static void add(final TreeSet<TaggedInt> low,
                            final TreeSet<TaggedInt> high, final int e) {
        (low.isEmpty() || e < low.last().value ? low : high)
                .add(new TaggedInt(e));
    }

    private static boolean remove(final TreeSet<TaggedInt> low,
                                  final TreeSet<TaggedInt> high, final int e) {
        final TaggedInt key = new TaggedInt(e);

        final TaggedInt fromLow = low.floor(key);
        if (fromLow != null && fromLow.value == e) {
            low.remove(fromLow);
            return true;
        }

        final TaggedInt fromHigh = high.floor(key);
        if (fromHigh != null && fromHigh.value == e) {
            high.remove(fromHigh);
            return true;
        }

        return false;
    }

    public static void main(final String[] args) {
        final TreeSet<TaggedInt> low = new TreeSet<>(), high = new TreeSet<>();

        try (final Scanner sc = new Scanner(System.in)) {
            for (int n = sc.nextInt(); n > 0; --n) {
                final String op = sc.next();
                final int arg = sc.nextInt();

                switch (op) {
                case "a":
                    add(low, high, arg);
                    break;

                case "r":
                    if (remove(low, high, arg)) break;

                    complain();
                    continue; // don't rebalance or print median if no change

                default:
                    throw new IllegalStateException("unrecognized query type");
                }

                rebalance(low, high);
                printMedianOrComplain(low, high);
            }
        }
    }

    private Solution() { throw new AssertionError(); }
}
