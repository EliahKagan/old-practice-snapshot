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

        void Paint(int distance, int i, int j)
        {
            if (i == -1 || i == n || j == -1 || j == n
                    || distance >= grid[i][j])
                return;

            grid[i][j] = distance;
            maxDistance = Math.Max(maxDistance, distance);
            queue.Enqueue((i, j));
        }

        while (queue.Count != 0) {
            var (i, j) = queue.Dequeue();
            var distance = grid[i][j] + 1;

            Paint(distance, i, j - 1);
            Paint(distance, i, j + 1);
            Paint(distance, i - 1, j);
            Paint(distance, i + 1, j);
        }

        return maxDistance;
    }
}
