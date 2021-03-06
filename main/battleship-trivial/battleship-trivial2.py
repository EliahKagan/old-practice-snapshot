#!/usr/bin/env python


from random import randint

def print_board(board): # outputs gameboard prettily
    for row in board:
        print ' '.join(row)

def random_row(board): # returns random row index
    return randint(0, len(board) - 1)

# returns random column index (assumes rectangular board)
def random_col(board):
    return randint(0, len(board[0]) - 1)

# initialize blank 5-by-5 gameboard
board = []
for x in range(5):
    board.append(['O'] * 5)

# greet user and show board
print "Let's play Battleship!"
print_board(board)

# place battleship in random cell
ship_row = random_row(board)
ship_col = random_col(board)

won_game = False

# allow the player four turns to guess the position
for turn in range(4):
    print 'Turn', turn + 1
    
    try:
        guess_row = int(raw_input('Guess Row:'))
        guess_col = int(raw_input('Guess Col:'))
    except ValueError:
        print "That's not even a whole number--turn forfeited!"
        continue
    
    if guess_row == ship_row and guess_col == ship_col:
        print 'Congratulations! You sunk my battleship!'
        won_game = True
        break
    elif not (0 <= guess_row < len(board)
                and 0 <= guess_col < len(board[0])):
        print "Oops, that's not even in the ocean."
    elif board[guess_row][guess_col] == 'X':
        print 'You guessed that one already.'
    else:
        print 'You missed my battleship!'
        board[guess_row][guess_col] = 'X'
    
    print_board(board)

if not won_game:
    print 'Game Over'
