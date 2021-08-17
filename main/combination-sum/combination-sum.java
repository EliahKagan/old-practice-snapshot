class Solution {
    private static final class Key {
        Key(final int index, final int subtot) {
            this.index = index;
            this.subtot = subtot;
        }

        boolean equals(final Key other) {
            return index == other.index && subtot == other.subtot;
        }

        @Override
        public boolean equals(final Object other) {
            // The Key class is a private (and final) implementation detail of
            // the combinationSum function, so it need not support equality
            // comparison against objects of other types.
            return equals((Key)other);
        }

        @Override
        public int hashCode() {
            // Based on the way described https://stackoverflow.com/a/31220250
            // by https://stackoverflow.com/users/2333021/christopher-rucinski.
            return (HASH_START * HASH_MUL + index) * HASH_MUL + subtot;
        }

        private final int index, subtot;

        private static final int HASH_START = 17, HASH_MUL = 31;
    }

    private static final class Node {
        Node(final int value, final int count, final Node next) {
            this.value = value;
            this.count = count;
            this.next = next;
        }

        List<Integer> toList() {
            final List<Integer> ret = new ArrayList<>();

            for (Node head = this; head != null; head = head.next) {
                for (int count = head.count; count != 0; --count)
                    ret.add(head.value);
            }

            return ret;
        }

        final int value, count;
        final Node next;
    }

    private static final List<Node> NO_WAYS = Collections.emptyList();

    private static final List<Node> TRIVIAL_WAY =
            Collections.singletonList(null);

    public List<List<Integer>> combinationSum(final int[] candidates,
                                              final int target) {
        final Map<Key, List<Node>> memo = new HashMap<>();

        final class Solver {
            private List<Node> solve(int index, int subtot) {
                if (subtot == 0) return TRIVIAL_WAY;
                if (index == candidates.length) return NO_WAYS;

                final Key key = new Key(index, subtot);
                List<Node> ways = memo.get(key);

                if (ways == null) {
                    ways = new ArrayList<>();
                    final int value = candidates[index++];
                    int count = 0;

                    for (; subtot >= 0; subtot -= value) {
                        for (final Node tail : solve(index, subtot))
                            ways.add(new Node(value, count, tail));

                        ++count;
                    }

                    memo.put(key, ways);
                }

                return ways;
            }
        }

        final List<Node> ways = new Solver().solve(0, target);
        final List<List<Integer>> ret = new ArrayList<>(ways.size());
        for (final Node way : ways) ret.add(way.toList());
        return ret;
    }
}
