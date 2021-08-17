#!/usr/bin/env python3

import itertools

# Files (in the sense of "rank and file") will be input alphabetically.
ALPHABET = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
assert all(ord(ALPHABET[i]) - ord(ALPHABET[0]) == i
           for i in range(len(ALPHABET)))

# The PLAYERS. Turns alternate between BLACK and WHITE.
WHITE = 0
BLACK = 1

def opponent(player):
    return 1 - player

assert opponent(WHITE) == BLACK and opponent(BLACK) == WHITE

# The PIECES. These represent what type of piece an object on the board is.
QUEEN = 0
KNIGHT = 1
BISHOP = 2
ROOK = 3
PAWN = 4

NTYPES = 5 # The number of PIECES, i.e., of _types_ of chessmen we know about.

def get_symbols():
    symbols_list = [None] * NTYPES

    symbols_list[QUEEN] = 'Q'
    symbols_list[KNIGHT] = 'N'
    symbols_list[BISHOP] = 'B'
    symbols_list[ROOK] = 'R'
    symbols_list[PAWN] = 'P'

    symbols = ''.join(symbols_list)
    assert len(symbols) == NTYPES
    return symbols

# The SYMBOLS. These are single characters. Each represents a PIECE.
SYMBOLS = get_symbols()

# The OBJECTS. As an internal detail of this simulation, each square of the
# board contains exactly one object, at any given time. Empty squares have the
# EMPTY object. Other squares have the (OBJ_RANGES[player].start + piece)
# object, where player is WHITE or BLACK and piece is one of the PIECES
# supported by this simulation.
EMPTY = 0
OBJ_RANGES = (range(1, 1 + NTYPES), range(1 + NTYPES, 1 + NTYPES * 2))
assert EMPTY < OBJ_RANGES[WHITE].start
assert OBJ_RANGES[WHITE].stop <= OBJ_RANGES[BLACK].start

def get_move_step_bundles():
    '''Gets the directions pieces can move in. Knights and kings change their
    positions by exactly these deltas. Other chessmen, besides pawns, change
    their positions by any positive multiple of them. That distinction is not
    covered here. Pawn behavior cannot be described in this way at all.'''
    # A knight in chess is mathematically a knight(a, b), where:
    a = 1
    b = 2

    steps = [None] * NTYPES

    steps[ROOK] = ((0, -1), (0, 1), (-1, 0), (1, 0))
    steps[BISHOP] = ((-1, -1), (-1, 1), (1, -1), (1, 1))
    steps[KNIGHT] = ((-a, -b), (-a, b), (a, -b), (a, b),
                     (-b, -a), (-b, a), (b, -a), (b, a))
    steps[QUEEN] = steps[ROOK] + steps[BISHOP]

    # Not defined for pawns, but defined for all other pieces.
    assert all((steps[piece] is None) == (piece == PAWN)
               for piece in range(NTYPES))

    return tuple(steps)

# The MOVE-STEP BUNDLES. As an internal detail of this simulation, a MOVE STEP
# is a vector representing the change in position corresponding either to one
# permitted move (itself) or to multiple permitted moves in the same direction
# (itself and its other positive mutliples). These vectors are represented as
# two-element tuples (di, dj) and each PIECE has a MOVE-STEP BUNDLE, which is a
# tuple whose elements are all the MOVE STEPS appropriate to that PIECE. See
# the documentation comment in get_move_step_bundles() for further details.
MOVE_STEP_BUNDLES = get_move_step_bundles()

# This simulation has no kings (nor pawns, but they wouldn't be covered here).
WALKS_MULTIPLE_STEPS = tuple(piece != KNIGHT for piece in range(NTYPES))

def get_directional_move_generator(step, multistep):
    '''Gets a function that, when called, returns an object that, when
    iterated, yields position deltas for how a particular (kind of) PIECE is
    allowed to move. The rules are provided by step, which is the MOVE STEP for
    the PIECE, and multistep, which says if multiples of the step (besides the
    step itself) are permitted. The multistep parameter should be True except
    for knights and kings, for which it should be False, and pawns, for which
    this function cannot be used.'''
    di, dj = step
    if multistep:
        return lambda: zip(itertools.count(di, di), itertools.count(dj, dj))
    else:
        return lambda: ((di, dj),)

def get_move_generators(piece):
    '''Gets MOVE GENERATORS for all directions permitted by any MOVE STEP in
    the MOVE-STEP BUNDLE for the specified PIECE.'''
    if piece == PAWN:
        return None

    multistep = WALKS_MULTIPLE_STEPS[piece]

    return tuple(get_directional_move_generator(step, multistep)
                 for step in MOVE_STEP_BUNDLES[piece])

MOVE_GENERATOR_BUNDLES = tuple(get_move_generators(piece)
                               for piece in range(NTYPES))

BOARD_SIZE = 4

def on_board(i, j):
    return 0 <= i < BOARD_SIZE and 0 <= j < BOARD_SIZE

VETERANS = (KNIGHT, BISHOP, ROOK) # pieces to which PAWN may be promoted
PROMOTES_AT_ROW = (BOARD_SIZE - 1, 0) # rows where each player's PAWNs promote
assert PROMOTES_AT_ROW[WHITE] != PROMOTES_AT_ROW[BLACK] == 0

PAWN_DIRECTIONS = (1, -1) # the directions of row changes by PAWNs
assert PAWN_DIRECTIONS[BLACK] < 0 < PAWN_DIRECTIONS[WHITE]

# The OFFSETS. These are constants for reading textual board representations.
ROW_OFFSET = 1                  # for each rank there shall be a row
COL_OFFSET = ord(ALPHABET[0])   # for each file there shall be a column

def get_empty_row():
    return [EMPTY] * BOARD_SIZE

def get_empty_board():
    return [get_empty_row() for _ in range(BOARD_SIZE)]

def as_piece(symbol):
    try:
        return SYMBOLS.index(symbol)
    except ValueError as e:
        raise ValueError('unknown chessman type "%s"' % symbol) from e

def add_obj(board, i, j, player, symbol):
    # Specially catch and rethrow just for the errors that are likely to result
    # from mistaken input or implementation bugs.
    if not (0 <= i < BOARD_SIZE and 0 <= j < BOARD_SIZE):
        raise IndexError('nonexistent board position')
    if board[i][j] != EMPTY:
        raise ValueError('board position already occupied')

    piece = as_piece(symbol)
    if piece == PAWN and i == PROMOTES_AT_ROW[player]:
        raise ValueError('a pawn in the final row would already be promoted')
    board[i][j] = OBJ_RANGES[player].start + piece

def read_initial_board(*counts): # call with (white_count, black_count)
    board = get_empty_board()

    for player in WHITE, BLACK:
        for _ in range(counts[player]):
            symbol, file_, rank_ = input().split()
            i = int(rank_) - ROW_OFFSET
            j = ord(file_) - COL_OFFSET
            add_obj(board, i, j, player, symbol)

    return board

def read_positive_record():
    record = list(map(int, input().split()))
    if any(value <= 0 for value in record):
        raise ValueError('unexpected nonpositive value')
    return record

def scan_nonpawn_moves(board, obj_range, o, i, j):
    for gen in MOVE_GENERATOR_BUNDLES[o - obj_range.start]:
        for ii, jj in ((i + di, j + dj) for di, dj in gen()):
            if not on_board(ii, jj) or board[ii][jj] in obj_range:
                break # Stop before hitting the edge or another of our pieces.

            yield o, ii, jj

            if board[ii][jj] != EMPTY:
                break # Stop after capturing one of our opponent's pieces.

def scan_pawn_moves(board, player, i, j):
    ii = i + PAWN_DIRECTIONS[player] # On board or it would've promoted before.

    opponent_obj_range = OBJ_RANGES[opponent(player)]
    def jjgen():
        if board[ii][j] == EMPTY:
            yield j
        for jj in j - 1, j + 1:
            if 0 <= jj < BOARD_SIZE and board[ii][jj] in opponent_obj_range:
                yield jj

    if ii == PROMOTES_AT_ROW[player]:
        for jj in jjgen():
            for veteran in VETERANS:
                yield OBJ_RANGES[player].start + veteran, ii, jj
    else:
        for jj in jjgen():
            yield OBJ_RANGES[player].start + PAWN, ii, jj

def scan_moves(board, player, o, i, j):
    '''Returns an iterable of new objects (in case of promotion) and positions
    that are permitted as results of the player moving o from (i, j), where
    obj_range is the player's _own_ object range (not that of the opponent).'''
    if o - OBJ_RANGES[player].start == PAWN:
        return scan_pawn_moves(board, player, i, j)
    else:
        return scan_nonpawn_moves(board, OBJ_RANGES[player], o, i, j)

def retrieve_obj_positions(board, obj_range):
    for i, j in itertools.product(range(BOARD_SIZE), range(BOARD_SIZE)):
        if board[i][j] in obj_range:
            yield board[i][j], i, j

for game in range(int(input())):
    white_count, black_count, moves_remaining = read_positive_record()
    board = read_initial_board(white_count, black_count)
    player = WHITE
    draw_wins = False

    def player_can_win():
        '''Determines if the player has a winning strategy.'''
        global moves_remaining, player, draw_wins
        if moves_remaining == 0:
            return draw_wins

        moves_remaining -= 1
        draw_wins = not draw_wins
        try:
            for o, i, j in retrieve_obj_positions(board, OBJ_RANGES[player]):
                for oo, ii, jj in scan_moves(board, player, o, i, j):
                    captured = board[ii][jj]
                    board[ii][jj] = oo
                    board[i][j] = EMPTY
                    player = opponent(player) # technically, it's the next turn
                    try:
                        if (captured == OBJ_RANGES[player].start + QUEEN
                                    or not player_can_win()):
                            return True
                    finally:
                        player = opponent(player) # backtracked to this turn
                        board[i][j] = o
                        board[ii][jj] = captured

            return False
        finally:
            draw_wins = not draw_wins
            moves_remaining += 1

    print('YES' if player_can_win() else 'NO')
