class Solution:
    def isValidSerialization(self, preorder):
        """
        :type preorder: str
        :rtype: bool
        """
        it = iter(preorder.split(','))

        def dfs():
            tok = next(it)
            if tok != '#':
                int(tok)  # check that the token represents an integer
                dfs()  # check the left subtree
                dfs()  # check the right subtree

        try:
            dfs()
        except (StopIteration, ValueError):
            return False

        try:
            next(it)
        except StopIteration:
            return True

        return False
