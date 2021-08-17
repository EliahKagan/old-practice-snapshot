import enum


GRID_SIZE = 1_000_000


@enum.unique
class State(enum.Enum):
    """Visitation states for cells in a grid."""
    BLOCKED = enum.auto()
    SOURCE = enum.auto()
    TARGET = enum.auto()


def neighbors(i: int, j: int):
    if i != 0:
        yield i - 1, j
    if i != GRID_SIZE:
        yield i + 1, j
    if j != 0:
        yield i, j - 1
    if j != GRID_SIZE:
        yield i, j + 1


class Solution:
    def isEscapePossible(self, blocked: List[List[int]],
                         source: List[int], target: List[int]) -> bool:
        max_enclosure = len(blocked)**2
        vis = {tuple(coords): State.BLOCKED for coords in blocked}
        start = tuple(source)
        finish = tuple(target)

        if start == finish:
            raise ValueError('source and target cells must not be the same')
        if finish in vis:
            return False

        vis[start] = State.SOURCE
        vis[finish] = State.TARGET
        source_fringe = [start]
        target_fringe = [finish]
        source_area = target_area = 1

        while (source_fringe and target_fringe and
                source_area < max_enclosure and target_area < max_enclosure):
            for nei in neighbors(*source_fringe.pop()):
                state = vis.setdefault(nei, State.SOURCE)
                if state is State.SOURCE:
                    source_area += 1
                    source_fringe.append(nei)
                elif state is State.TARGET:
                    return True

            for nei in neighbors(*target_fringe.pop()):
                state = vis.setdefault(nei, State.TARGET)
                if state is State.TARGET:
                    target_area += 1
                    target_fringe.append(nei)
                elif state is State.SOURCE:
                    return True

        print(source_area, target_area, max_enclosure)  # FIXME: remove after debugging
        print(len(source_fringe), len(target_fringe))  # FIXME: remove after debugging
        return bool(source_fringe and target_fringe)
