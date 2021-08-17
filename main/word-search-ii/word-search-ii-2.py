class Solution:
    @staticmethod
    def findWords(board: List[List[str]], words: List[str]) -> List[str]:
        """Finds words on a board."""
        return sorted(boggle(board, build_trie(words))) if board else []


# Can be anything other than a character that can appear in a word.
WORD_MARK = None


def build_trie(words):
    """Builds a trie from the provided word list."""
    trie = {}

    for word in words:
        add_word(trie, word)

    return trie


def add_word(trie, word):
    """Adds a chain to the trie for the word."""
    node = trie

    for ch in word:
        try:
            node = node[ch]
        except KeyError:
            child = {}
            node[ch] = child
            node = child

    node[WORD_MARK] = word


def boggle(board, trie):
    """Searches for words on the assumed-nonempty board."""
    height = len(board)
    width = len(board[0])
    matches = set()

    def dfs(i, j, node):
        if not (0 <= i < height and 0 <= j < width):
            return

        ch = board[i][j]
        if ch is None:
            return

        try:
            child = node[ch]
        except KeyError:
            return

        try:
            word = child[WORD_MARK]
        except KeyError:
            pass
        else:
            matches.add(word)

        board[i][j] = None
        dfs(i, j - 1, child)
        dfs(i, j + 1, child)
        dfs(i - 1, j, child)
        dfs(i + 1, j, child)
        board[i][j] = ch

    for i in range(height):
        for j in range(width):
            dfs(i, j, trie)

    return matches
