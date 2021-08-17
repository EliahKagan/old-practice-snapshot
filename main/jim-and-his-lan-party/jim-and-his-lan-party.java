import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.PrimitiveIterator;
import java.util.StringJoiner;
import java.util.StringTokenizer;
import java.util.stream.IntStream;

/** A disjoint-set union data structure, with elements/vertices called players,
 * where each vertex has a color called a game, and where each disjoint set
 * tracks how many players of each game (vertices of each color) it contains.
 * Each connect() operation increments a clock, and the times at which each game
 * (color) has all its players (vertices) connected in a single component,
 * possibly also connecte to players of other games (vertices of other colors),
 * is made available by enumerating the DisjointPlayerSets object. */
final class DisjointPlayerSets implements Iterable<Integer> {
    /** Initializes the disjoint sets of players with player -> game mappings
     * held by each disjoint set's leader.
     * @param playerGames   Player i will play the game playerGames[i].
     * @param gameCount     Games will be in the range [0, gameCount). */
    DisjointPlayerSets(final int[] playerGames, final int gameCount) {
        final int playerCount = playerGames.length;

        _contribs = new ArrayList<>(playerCount);
        while (_contribs.size() != playerCount) _contribs.add(null);

        _parentsOrRanks = new int[playerCount];
        Arrays.fill(_parentsOrRanks, -1);

        _popTargetsOrStartTimes = new int[gameCount];

        // determine how many players are needed for each game
        for (final int game : playerGames) --_popTargetsOrStartTimes[game];

        // start single-player games immediately
        for (int game = 0; game != gameCount; ++game) {
            if (_popTargetsOrStartTimes[game] ==  -1)
                _popTargetsOrStartTimes[game] = 0;
        }

        // record players' population contributions toward multiplayer games
        for (int player = 0; player != playerCount; ++player) {
            final Map<Integer, Integer> contrib = new HashMap<>();
            contrib.put(playerGames[player], -1);
            _contribs.set(player, contrib);
        }
    }

    /** Advances the clock, joining and merging players' contributions.
     * @param player1   One endpoint of the new player-to-player edge.
     * @param player2   The other endpoint of the new player-to-player edge. */
    void connect(final int player1, final int player2) {
        // one connection per tick of the clock
        ++_time;

        // actually connect the sublans (if they are separate)
        final int[] leaders = union(player1, player2);

        // unless the sublans were already joined, merge their contributions
        if (leaders != null) mergeContribs(leaders[0], leaders[1]);
    }

    /** Obtains an iterator that iterates through game start times, measured as
     * the number of connections that have been made, or -1 if not started. */
    @Override
    public PrimitiveIterator.OfInt iterator() {
        return new Itr(IntStream.of(_popTargetsOrStartTimes).iterator());
    }

    /** A simple wrapper around a PrimitiveIterator.OfInt, collapsing all
     * negative values to the special GAME_NOT_STARTED value (-1). */
    private static final class Itr implements PrimitiveIterator.OfInt {
        /** When a game is not started, this is reported as its start time. */
        private static final int GAME_NOT_STARTED = -1;

        Itr(final PrimitiveIterator.OfInt itr) {
            _itr = itr;
        }

        @Override
        public boolean hasNext() {
            return _itr.hasNext();
        }

        @Override
        public int nextInt() {
            final int next = _itr.nextInt();
            return next < 0 ? GAME_NOT_STARTED : next;
        }

        private final PrimitiveIterator.OfInt _itr;
    }

    /** Finds the leader of the player's connected sublan.
     * @param player    The player whose leader is sought.
     * @return The leader of the se the player belongs to. */
    private int findSet(int player) {
        // find the leader
        int leader = player;
        while (_parentsOrRanks[leader] >= 0) leader = _parentsOrRanks[leader];

        // compress the path
        while (player != leader) {
            final int parent = _parentsOrRanks[player];
            _parentsOrRanks[player] = leader;
            player = parent;
        }

        return leader;
    }

    /** Unites sublans by rank if they were separate.
     * @param player1   An element of the first disjoint set being united.
     * @param player2   An element of the second disjoint set being united.
     * @return The old leaders as {parent, child}, or null if already united. */
    private int[] union(int player1, int player2) {
        // find the leaders and stop if they are the same
        player1 = findSet(player1);
        player2 = findSet(player2);
        if (player1 == player2) return null;

        // unite by rank
        if (_parentsOrRanks[player1] > _parentsOrRanks[player2]) {
            // player2 has superior (more negative) rank, so it will stay leader
            final int tmp = player1;
            player1 = player2;
            player2 = tmp;
        }
        else if (_parentsOrRanks[player1] == _parentsOrRanks[player2]) {
            // the players have equal rank, so promote player1
            --_parentsOrRanks[player1];
        }

        // whichever player is currently player1 gets to remain a leader
        _parentsOrRanks[player2] = player1;
        return new int[] { player1, player2 };
    }

    /** Merges the population contributions of what had been two sublans.
     * @param destPlayer    The player to take and add the mappings.
     * @param srcPlayer     The player to give and drop the mappings. */
    private void mergeContribs(final int destPlayer, final int srcPlayer) {
        Map<Integer, Integer> src = _contribs.get(srcPlayer);
        if (src == null) return;

        _contribs.set(srcPlayer, null);

        Map<Integer, Integer> dest = _contribs.get(destPlayer);
        if (dest == null) {
            _contribs.set(destPlayer, src);
            return;
        }

        if (dest.size() < src.size()) {
            final Map<Integer, Integer> tmp = dest;
            dest = src;
            src = tmp;

            _contribs.set(destPlayer, dest);
        }

        mergeNontrivialContribs(dest, src);
        if (dest.isEmpty()) _contribs.set(destPlayer, null);
    }

    /** Merges two (game, neg. population) hashes, removing and recording start
     * times for games that have just reached their starting populations.
     * @param dest  The hash receiving the mappings.
     * @param src   The hash providing the mappings. */
    private void mergeNontrivialContribs(final Map<Integer, Integer> dest,
                                         final Map<Integer, Integer> src) {
        src.forEach((game, negativePopulation) ->
            dest.merge(game, negativePopulation, (destNegPop, srcNegPop) -> {
                final int negPop = destNegPop + srcNegPop;
                if (negPop != _popTargetsOrStartTimes[game]) return negPop;

                _popTargetsOrStartTimes[game] = _time;
                return null;
            })
        );
    }

    /** set leader -> (game -> negative population) */
    private final List<Map<Integer, Integer>> _contribs;

    /** player -> nonnegative DSU parent, or negative DSU rank if set leader */
    private final int[] _parentsOrRanks;

    /** game -> negative population target, or nonneg. start time if started */
    private final int[] _popTargetsOrStartTimes;

    /** current time, n ticks, for the simulation (one connection per tick) */
    private int _time = 0;
}

final class Parser implements AutoCloseable {
    Parser(final InputStream in) {
        _reader = new BufferedReader(new InputStreamReader(in));
    }

    @Override
    public void close() throws IOException {
        _reader.close();
    }

    int readDown() throws IOException {
        _tokenizer = new StringTokenizer(_reader.readLine());
        return readAcross();
    }

    int readAcross() {
        return Integer.parseInt(_tokenizer.nextToken());
    }

    private final BufferedReader _reader;

    private StringTokenizer _tokenizer;
}

final class Solution {
    public static void main(final String[] args) throws IOException {
        try (final Parser parser = new Parser(System.in)) {
            // read initial parameters
            final int n = parser.readDown(), m = parser.readAcross();
            int q = parser.readAcross();

            // read everyone's game and initialize the model
            // (adding one to the game count, for 1-based indexing)
            final DisjointPlayerSets network = new DisjointPlayerSets(
                    readPlayerGames(parser, n), m + 1);

            // read all the connections and apply them to the model in order
            while (q-- > 0) {
                final int u = parser.readDown(), v = parser.readAcross();
                network.connect(u, v);
            }

            // output each game's start time
            final StringJoiner sj = new StringJoiner(System.lineSeparator());
            final PrimitiveIterator.OfInt it = network.iterator();
            it.next(); // skip the 0 in the unused first position
            it.forEachRemaining((int time) -> sj.add(Integer.toString(time)));
            System.out.println(sj);
        }
    }

    /** Produces a list of 0 followed by numbers read from a single line. */
    private static int[] readPlayerGames(final Parser parser, final int n)
            throws IOException {
        if (n <= 0)
            throw new IllegalArgumentException("player count must be positive");

        final int[] playerGames = new int[n + 1];

        playerGames[1] = parser.readDown();
        for (int i = 2; i != playerGames.length; ++i)
            playerGames[i] = parser.readAcross();

        return playerGames;
    }

    private Solution() { throw new AssertionError(); }
}
