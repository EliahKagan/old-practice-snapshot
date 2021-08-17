import java.util.ArrayList;
import java.util.Arrays;
import java.util.ConcurrentModificationException;
import java.util.List;

/** Tracks frequencies of items and knows if it has at least one of each. */
final class AndCounter {
    AndCounter(final int size) {
        _counts = new int[size];
        _missing = size;
    }

    void add(final int item) {
        if (_counts[item]++ == 0) --_missing;
    }

    void remove(final int item) {
        if (--_counts[item] == 0) ++_missing;
    }

    boolean atGoal() {
        return _missing == 0;
    }

    private final int[] _counts;

    private int _missing;
}

/** A value that remembers what row it came from. */
final class Element implements Comparable<Element> {
    Element(final int value, final int rowId) {
        this.value = value;
        this.rowId = rowId;
    }

    public int compareTo(final Element other) {
        return Integer.compare(value, other.value);
    }

    final int value, rowId;
}

class Solution {
    public int[] smallestRange(final List<List<Integer>> nums) {
        final Element[] elems = flatten(nums);
        Arrays.sort(elems);
        return findMinRangeCoveringAllGroups(elems, nums.size());
    }

    private static Element[] flatten(final List<List<Integer>> nums) {
        final Element[] elems = new Element[getTotalLength(nums)];

        int k = 0;
        for (int rowId = 0; rowId != nums.size(); ++rowId) {
            for (final int value : nums.get(rowId))
                elems[k++] = new Element(value, rowId);
        }

        if (k != elems.length) throw new ConcurrentModificationException();
        return elems;
    }

    private static <T> int getTotalLength(final List<List<T>> rows) {
        int len = 0;
        for (final List<T> row : rows) len += row.size();
        return len;
    }

    private static int[] findMinRangeCoveringAllGroups(final Element[] elems,
                                                       final int rowCount) {
        int start = elems[0].value, stop = elems[elems.length - 1].value;
        final AndCounter targets = new AndCounter(rowCount);

        for (int left = -1, right = -1; ; ) {
            while (!targets.atGoal() && ++right != elems.length)
                targets.add(elems[right].rowId);

            if (right == elems.length) break;

            while (targets.atGoal())
                targets.remove(elems[++left].rowId);

            if (elems[right].value - elems[left].value < stop - start) {
                start = elems[left].value;
                stop = elems[right].value;
            }
        }

        return new int[] { start, stop };
    }
}

final class UnitTest {
    public static void main(final String[] args) {
        final int[][] a = {
                {4, 10, 15, 24, 26},
                {0, 9, 12, 20},
                {5, 18, 22, 30}
        };

        test(a);

        final int[][] b = {
                {-39188, -19118},
                {-92167, -74585, -71372, -68941, -66699, -66541, -65520, -61363, -47182, -42837, -42606, -4518, 12948, 18858, 24820, 36209, 55066, 64917, 65611, 82101, 90910, 91233},
                {-54216, -22937, -17115, -1603, 2167, 36929},
                {-94402, -57858, -48916, -38906, -27238, -615, 43439, 57426, 88482},
                {-90879, -88451, -86193, -84039, -83226, -82043, -76734, -70728, -68704, -64036, -61383, -56726, -56542, -50342, -40026, -29768, -27798, -25701, -22833, -21175, -18805, -17066, -16382, -1192, 1599, 7103, 7759, 12194, 19076, 24753, 30678, 31160, 47688, 53150, 56513, 57693, 58054, 58876, 61753, 66660, 67005, 69236, 70360, 77765, 80622, 85875, 87923, 89693, 91719, 93501, 93756, 93965, 98746, 98751, 99624},
                {-93492, -75274, -75042, -73965, -70584, -67383, -62776, -59901, -47608, -46677, -46256, -22718, -13115, -12702, -11416, -10030, -7529, 1512, 5804, 8803, 12381, 19380, 24865, 24983, 28389, 39141, 42273, 45040, 59032, 73663, 74333, 82422, 87044, 87495, 93470, 97758, 99008},
                {-99615, -96435, -94713, -84516, -84092, -83271, -83196, -82663, -81339, -79318, -72884, -72814, -72266, -72059, -63513, -59654, -54579, -53893, -48416, -48342, -44555, -34252, -21257, -20760, -17101, -17093, -16354, -13770, -5325, -2980, -2047, -2041, -1876, 5721, 5850, 7217, 15316, 18064, 18490, 24318, 30518, 37714, 38240, 43405, 47303, 47405, 56965, 60219, 62012, 64024, 68853, 68948, 68987, 71759, 72264, 74765, 76709, 86777, 86947, 87933, 97352},
                {-91797, -87698, -84590, -81956, -74207, -73699, -72692, -72516, -67008, -62520, -61792, -61466, -53035, -44200, -36235, -30447, -27236, -21593, -20133, -17521, -14713, -13694, -12818, -2842, -424, 6649, 10498, 12692, 17478, 26721, 27276, 28361, 30913, 41900, 50333, 52277, 53232, 57268, 57832, 67006, 78180, 78218, 81042, 86146, 86596, 89450},
                {-99254, -91367, -90384, -89507, -88167, -87488, -86508, -85257, -85130, -84787, -80724, -80327, -79068, -78644, -74888, -72647, -70801, -66180, -65235, -65118, -65013, -63480, -62578, -57156, -54835, -50920, -50626, -48537, -48472, -48267, -39760, -38004, -37883, -36034, -33527, -31950, -31155, -28798, -25985, -25818, -22702, -21719, -15520, -15037, -6593, -4347, -4307, -3746, -3170, 1567, 5657, 8100, 10270, 10644, 12976, 14458, 15675, 17582, 18572, 20304, 25305, 31757, 36520, 37121, 37713, 39530, 40236, 47942, 49216, 51242, 53337, 53540, 54578, 54726, 55794, 57054, 58971, 63471, 65853, 66177, 69514, 71366, 72327, 77827, 80458, 88078, 90180, 99435},
        };

        test(b);
    }

    private static void test(final int[][] a) {
        final List<List<Integer>> nums = new ArrayList<>(a.length);

        for (final int[] row : a) {
            final List<Integer> numsRow = new ArrayList<>(row.length);
            for (final int e : row) numsRow.add(e);
            nums.add(numsRow);
        }

        final int[] range = new Solution().smallestRange(nums);
        System.out.println(Arrays.toString(range));
    }
}
