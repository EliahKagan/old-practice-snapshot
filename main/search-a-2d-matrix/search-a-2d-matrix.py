class FlatView(object):
    def __init__(self, matrix):
        self._matrix = matrix
        self._width = len(matrix[0]) if matrix else 0

    def __repr__(self):
         return '<FlatView width:{} matrix:{}>'.format(self._width,
                                                       repr(self._matrix))

    def __str__(self):
        return str(self._matrix)

    def __bool__(self):
        return self._width != 0

    def __len__(self):
        return len(self._matrix) * self._width

    def __iter__(self):
        return itertools.chain.from_iterable(self._matrix)

    def __getitem__(self, index):
        if self:
            return self._matrix[index // self._width][index % self._width]
        else:
            raise IndexError('empty view cannot be indexed')

class Solution:
    def searchMatrix(self, matrix, target):
        """
        :type matrix: List[List[int]]
        :type target: int
        :rtype: bool
        """
        try:
            view = FlatView(matrix)
            return view[bisect.bisect_left(view, target)] == target
        except IndexError:
            return False
