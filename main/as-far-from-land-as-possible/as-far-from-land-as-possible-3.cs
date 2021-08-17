public class Solution {
    /// <summary>Finds the water cell farthest from land.</summary>
    /// <remarks>Mutates the grid.</remarks>
    /// <returns>
    /// The maximum from land to water, or -1 if there is no solution.
    /// </returns>
    public int MaxDistance(int[][] grid)
    {
        var n = grid.Length;
        if (n == 0) return -1;

        var queue = new Queue<(int, int)>();

        // Rewrite the grid to hold closest known distances from land, and
        // populate the queue with coordinates of all land cells.
        for (var i = 0; i != n; ++i) {
            for (var j = 0; j != n; ++j) {
                if (grid[i][j] == 0) {
                    // water
                    grid[i][j] = int.MaxValue;
                } else {
                    // land
                    grid[i][j] = 0;
                    queue.Enqueue((i, j));
                }
            }
        }

        var maxDistance = -1;

        while (queue.Count != 0) {
            var (i, j) = queue.Dequeue();
            var distance = grid[i][j] + 1;

            foreach (var (h, k) in new[] {(i, j - 1), (i, j + 1),
                                          (i - 1, j), (i + 1, j)}) {
                if (h == -1 || h == n || k == -1 || k == n
                        || distance >= grid[h][k])
                    continue;

                grid[h][k] = distance;
                maxDistance = Math.Max(maxDistance, distance);
                queue.Enqueue((h, k));
            }
        }

        return maxDistance;
    }
}
