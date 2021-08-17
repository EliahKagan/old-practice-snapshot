public class Solution {
    public int[,] FloodFill(int[,] image, int sr, int sc, int newColor) {
        var oldColor = image[sr, sc];
        if (oldColor == newColor) return image;

        var m = image.GetLength(0);
        var n = image.GetLength(1);

        void Fill(int i, int j) {
            if (i != -1 && i != m && j != -1 && j != n
                                  && image[i, j] == oldColor) {
                image[i, j] = newColor;
                Fill(i - 1, j);
                Fill(i + 1, j);
                Fill(i, j - 1);
                Fill(i, j + 1);
            }
        }

        Fill(sr, sc);
        return image;
    }
}
