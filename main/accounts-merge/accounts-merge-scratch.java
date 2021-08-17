import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.StringJoiner;
import java.util.stream.Collectors;
import java.util.stream.Stream;

final class DisjointSetElement {
    DisjointSetElement findSet() {
        DisjointSetElement ret = this;
        while (ret._parent != ret) ret = ret._parent;

        for (DisjointSetElement cur = this; cur != ret; ) {
            final DisjointSetElement next = cur._parent;
            cur._parent = ret;
            cur = next;
        }

        return ret;
    }

    void union(final DisjointSetElement other) {
        final DisjointSetElement a = findSet(), b = other.findSet();

        if (a._rank < b._rank) {
            a._parent = b;
        } else {
            if (a._rank == b._rank) ++a._rank;
            b._parent = a;
        }
    }

    private DisjointSetElement _parent = this;

    private int _rank = 0;
}

final class DisjointSets implements Iterable<Stream<String>> {
    public void put(final Iterator<String> subset) {
        if (subset.hasNext()) {
            final DisjointSetElement first = getElement(subset.next());
            subset.forEachRemaining(cur -> getElement(cur).union(first));
        }
    }

    public Iterator<Stream<String>> iterator() {
        return _elems.entrySet().stream()
                .collect(Collectors.groupingBy(kv -> kv.getValue().findSet()))
                .values().stream()
                .map(group -> group.stream().map(Map.Entry::getKey).sorted())
                .iterator();
    }

    public void clear() {
        _elems.clear();
    }

    private DisjointSetElement getElement(final String key) {
        return _elems.computeIfAbsent(key, k -> new DisjointSetElement());
    }

    private final Map<String, DisjointSetElement> _elems = new HashMap<>();
}

final class Account {
    static String name(final Iterable<String> account) {
        return account.iterator().next();
    }

    static Iterator<String> emails(final Iterable<String> account) {
        final Iterator<String> ret = account.iterator();
        ret.next();
        return ret;
    }

    private Account() { throw new AssertionError(); }
}

class Solution {
    public List<List<String>>
    accountsMerge(final List<List<String>> accounts) {
        final List<List<String>> ret = new ArrayList<>();
        final DisjointSets sets = new DisjointSets();

        accounts.stream().collect(Collectors.groupingBy(Account::name))
                         .forEach((name, group) -> {
            group.stream().map(Account::emails).forEachOrdered(sets::put);

            for (final Stream<String> set : sets) {
                ret.add(Stream.concat(Stream.of(name), set)
                              .collect(Collectors.toList()));
            }

            sets.clear();
        });

        return ret;
    }
}

final class UnitTest {
    public static void main(final String[] args) {
        final List<List<String>> accounts =  List.of(
                List.of("John", "johnsmith@mail.com", "john00@mail.com"),
                List.of("John", "johnnybravo@mail.com"),
                List.of("Sheila"),
                List.of("John", "johnsmith@mail.com", "john_newyork@mail.com"),
                List.of("Mary", "mary@mail.com")
        );

        new Solution().accountsMerge(accounts).forEach(account -> {
            final StringJoiner sj = new StringJoiner("\", \"", "[\"", "\"]");
            account.forEach(sj::add);
            System.out.println(sj);
        });
    }

    private UnitTest() { throw new AssertionError(); }
}
