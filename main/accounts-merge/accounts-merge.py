class DisjointSetElement(object):
    def __init__(self):
        self._parent = self
        self._rank = 0

    def findSet(self):
        ret = self
        while ret._parent is not ret:
            ret = ret._parent

        cur = self
        while cur is not ret:
            nxt = cur._parent
            cur._parent = ret
            cur = nxt

        return ret

    def union(self, other):
        a = self.findSet()
        b = other.findSet()

        if (a._rank < b._rank):
            a._parent = b
        else:
            if a._rank == b._rank:
                a._rank += 1
            b._parent = a

class DisjointSets(object):
    def __init__(self):
        self._elems = collections.defaultdict(DisjointSetElement)

    def __iter__(self):
        groups = collections.defaultdict(list)
        for text, elem in self._elems.items():
            groups[elem.findSet()].append(text)

        for texts in groups.values():
            texts.sort()
            yield texts

    def add(self, subset):
        try:
            it = iter(subset)
            first = self._elems[next(it)]
        except StopIteration:
            return

        for cur in it:
            self._elems[cur].union(first)

    def clear(self):
        self._elems.clear()

class Account(object):
    __init__ = None

    @staticmethod
    def name(account):
        return next(iter(account))

    @staticmethod
    def emails(account):
        return itertools.islice(account, 1, None)

class Solution:
    def accountsMerge(self, accounts):
        """
        :type accounts: List[List[str]]
        :rtype: List[List[str]]
        """
        # groups is a map of name -> table, where each row in the table lists
        # email addresses known to belong to the same person, but different
        # rows MIGHT contain email addresses belonging to different people who
        # happen to have the same name.
        groups = collections.defaultdict(list)
        for account in accounts:
            groups[Account.name(account)].append(Account.emails(account))

        ret = []
        sets = DisjointSets()

        for name, table in groups.items():
            for row in table:
                sets.add(row)
            for emails in sets:
                emails.insert(0, name)
                ret.append(emails)
            sets.clear()

        return ret
