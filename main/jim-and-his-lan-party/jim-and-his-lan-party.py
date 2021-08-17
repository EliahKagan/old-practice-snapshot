#!/usr/bin/env python3

import collections
import itertools

class DisjointPlayerSets:
    def __init__(self, player_games, game_count):
        '''Initializes from player -> game mappings in player_games.'''
        player_count = len(player_games)

        # set leader -> (game -> negative population)
        self._contribs = [None] * player_count

        # player -> nonnegative DSU parent, or negative DSU rank if set leader
        self._parents_or_ranks = [-1] * player_count

        # game -> negative population target, or nonneg. start time if started
        self._pop_targets_or_start_times = [0] * game_count

        # current time, in ticks, for the simulation (one connection per tick)
        self._time = 0

        # determine how many players are needed for each game
        for game in player_games:
            self._pop_targets_or_start_times[game] -= 1

        # start single-player games immediately
        for game, pop_target in enumerate(self._pop_targets_or_start_times):
            if pop_target == -1:
                self._pop_targets_or_start_times[game] = 0

        # record players' population contributions toward multiplayer games
        for player, game in enumerate(player_games):
            if self._pop_targets_or_start_times[game] != 0:
                contrib = collections.Counter()
                contrib[game] -= 1
                self._contribs[player] = contrib

    def __iter__(self, game_not_started = -1):
        '''Iterates through game start times.'''
        return ((game_not_started if start_time < 0 else start_time)
                for start_time in self._pop_targets_or_start_times)

    def connect(self, player1, player2):
        '''Advances the clock, joining and merging players' contributions.'''
        # one connection per tick of the clock
        self._time += 1

        # actually connect the sublans (if they are separate)
        dest_player, src_player = self._union(player1, player2)

        # unless the sublans were already joined, merge their contributions
        if dest_player is not None:
            self._merge_contribs(dest_player, src_player)

    def _find_set(self, player):
        '''Finds the leader of the player's connected sublan.'''
        # find the leader
        leader = player
        while self._parents_or_ranks[leader] >= 0:
            leader = self._parents_or_ranks[leader]

        # compress the path
        while player != leader:
            self._parents_or_ranks[player], player \
                    = leader, self._parents_or_ranks[player]

        return leader

    def _union(self, player1, player2):
        '''
        Unites the sublans by rank if they were separate and returns original
        leaders as a tuple (parent, child). If the players are in the same
        sublan already, returns (None, None) and doesn't alter connectivity.
        '''
        # find the leaders and stop if they are the same
        player1 = self._find_set(player1)
        player2 = self._find_set(player2)
        if player1 == player2:
            return None, None

        # unite by rank
        if self._parents_or_ranks[player1] > self._parents_or_ranks[player2]:
            # player 2 has superior (more negative) rank; it remains the leader
            player1, player2 = player2, player1
        elif self._parents_or_ranks[player1] == self._parents_or_ranks[player2]:
            # players have equal rank, so promote player1
            self._parents_or_ranks[player1] -= 1

        # whichever player is currently player1 remains the leader
        self._parents_or_ranks[player2] = player1
        return player1, player2

    def _merge_contribs(self, dest_player, src_player):
        '''Merges the population contributions of what had been two sublans.'''
        src = self._contribs[src_player]
        if src is None:
            return

        self._contribs[src_player] = None

        dest = self._contribs[dest_player]
        if dest is None:
            self._contribs[dest_player] = src
            return

        if len(dest) < len(src):
            dest, src = src, dest
            self._contribs[dest_player] = dest

        self._merge_nontrivial_contribs(dest, src)
        if not dest:
            self._contribs[dest_player] = None

    def _merge_nontrivial_contribs(self, dest, src):
        '''
        Merges two (game, population) dicts, removing and recording start
        times for games that have just reached their starting populations.
        '''
        for game, negative_population in src.items():
            negative_population += dest[game]
            if negative_population == self._pop_targets_or_start_times[game]:
                self._pop_targets_or_start_times[game] = self._time
                del dest[game]
            else:
                dest[game] = negative_population

def read_record():
    return map(int, input().split())

def read_player_games(n):
    '''Produces a list of 0 followed by numbers read from a single line.'''
    player_games = list(itertools.chain((0,), read_record()))

    if len(player_games) != n + 1: # plus one (the 0) for 1-based indexing
        raise ValueError('wrong record length')

    return player_games

# read initial parameters
n, m, q = read_record()

# read everyone's game and initialize the model (plus one for 1-based indexing)
network = DisjointPlayerSets(read_player_games(n), m + 1)

# read connection information and apply all the connections in order
for _ in range(q):
    u, v = read_record()
    network.connect(u, v)

# output each game's start time
print('\n'.join(map(str, itertools.islice(network, 1, None))))
