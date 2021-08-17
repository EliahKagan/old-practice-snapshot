#!/usr/bin/env ruby
$VERBOSE = true

# When a game has not started, this value is reported as its start time.
GAME_NOT_STARTED = -1

# A disjoint-set union data structure, with elements/vertices called players,
# where each vertex has a color called a game, and where each disjoint set
# tracks how many players of each game (vertices of each color) it contains.
# Each connect() operation increments a clock, and the times at which each game
# (color) has all its players (vertices) connected in a single component,
# possibly also connected to players of other games (vertices of other colors),
# is made available by enumerating the DisjointPlayerSets object.
class DisjointPlayerSets
  include Enumerable

  # Initializes the disjoint sets of players with player -> game mappings held
  # by each disjoint set's leader.
  # @param player_games   Player i will play the game player_games[i].
  # @param game_count     Games will be in the range [0, game_count)
  def initialize(player_games, game_count)
    player_count = player_games.size

    # set leader -> (game -> negative population)
    @contribs = Array.new(player_count)

    # player -> nonnegative DSU parent, or negative DSU rank if set leader
    @parents_or_ranks = Array.new(player_count, -1)

    # game -> negative population target, or nonnegative start time if started
    @pop_targets_or_start_times = Array.new(game_count, 0)

    # current time, in ticks, for the simulation (one connection per tick)
    @time = 0

    # determine how many players are needed for each game
    player_games.each { |game| @pop_targets_or_start_times[game] -= 1 }

    # start single-player games immediately
    @pop_targets_or_start_times.each_with_index do |neg_pop_target, game|
      @pop_targets_or_start_times[game] = 0 if neg_pop_target == -1
    end

    # record players' population contributions toward multiplayer games
    player_games.each_with_index do |game, player|
      contrib = Hash.new(0)
      contrib[game] = -1
      @contribs[player] = contrib
    end
  end

  # Iterates through game start times.
  def each
    return to_enum unless block_given?

    @pop_targets_or_start_times.each do |start_time|
      yield start_time.negative? ? GAME_NOT_STARTED : start_time
    end
  end

  # Advances the clock, joining and merging players' contributions.
  # @param player1  One endpoint of the new player-to-player edge.
  # @param player2  The other endpoint of the new player-to-player edge.
  def connect(player1, player2)
    # one connection per tick of the clock
    @time += 1

    # actually connect the sublans (if they are separate)
    dest_player, src_player = union(player1, player2)

    # unless the sublans were already joined, merge their contributions
    merge_contribs(dest_player, src_player) unless dest_player.nil?
    nil
  end

  # Finds the leader of the player's connected sublan.
  # @param player   The player whose leader is sought.
  # @return The leader of the set the player belongs to.
  private def find_set(player)
    # find the leader
    leader = player
    leader = @parents_or_ranks[leader] while @parents_or_ranks[leader] >= 0

    # compress the path
    while player != leader
      parent = @parents_or_ranks[player]
      @parents_or_ranks[player] = leader
      player = parent
    end

    leader
  end

  # Unites sublans by rank if they were separate.
  # @param player1  An element of the first disjoint set being united.
  # @param player2  An element of the second disjoint set being united.
  # @return The old leaders as [parent, child], or nil if already united.
  private def union(player1, player2)
    # find the leaders and stop if they are the same
    player1 = find_set(player1)
    player2 = find_set(player2)
    return nil if player1 == player2

    # unite by rank
    if @parents_or_ranks[player1] > @parents_or_ranks[player2]
      # player 2 has superior (more negative) rank; swap so it stays the leader
      player1, player2 = player2, player1
    elsif @parents_or_ranks[player1] == @parents_or_ranks[player2]
      # the players have equal rank, so promote player1
      @parents_or_ranks[player1] -= 1
    end

    # whichever player is currently player1 gets to remain a leader
    @parents_or_ranks[player2] = player1
    [player1, player2]
  end

  # Merges the population contributions of what had been two sublans.
  # @param dest_player  The player to take and add the mappings.
  # @param src_player   The player to give and drop the mappings.
  private def merge_contribs(dest_player, src_player)
    src = @contribs[src_player]
    return if src.nil?

    @contribs[src_player] = nil

    dest = @contribs[dest_player]
    if dest.nil?
      @contribs[dest_player] = src
      return
    end

    if dest.size < src.size
      dest, src = src, dest
      @contribs[dest_player] = dest
    end

    merge_nontrivial_contribs(dest, src)
    @contribs[dest_player] = nil if dest.empty?
  end

  # Merges two (game, negative population) hashes, removing and recording start
  # times for games that have just reached their starting populations.
  # @param dest   The hash receiving the mappings.
  # @param src    The hash providing the mappings.
  private def merge_nontrivial_contribs(dest, src)
    src.each do |game, neg_pop|
      next unless (dest[game] += neg_pop) == @pop_targets_or_start_times[game]
      @pop_targets_or_start_times[game] = @time
      dest.delete(game)
    end
  end
end

def read_record
  gets.split.map!(&:to_i)
end

# Produces a list of 0 followed by numbers read from a single line.
def read_player_games(n)
  player_games = read_record
  raise 'wrong record length' if player_games.size != n
  player_games.unshift(0)
end

# read initial parameters
n, m, q = read_record

# read everyone's game and initialize the model (plus one for 1-based indexing)
network = DisjointPlayerSets.new(read_player_games(n), m + 1)

# read connection information and apply all the connections in order
q.times { network.connect(*read_record) }

# output each game's start time
puts(*network.lazy.drop(1))
