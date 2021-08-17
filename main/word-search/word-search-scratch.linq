<Query Kind="Program" />

public class Solution {
    public bool Exist(char[,] board, string word) {
        const char visited = '\0';
        var istop = board.GetLength(0);
        var jstop = board.GetLength(1);
        var kstop = word.Length;
        var k = 0;
        
        bool Dfs(int i, int j)
        {
            if (i == -1 || i == istop || j == -1 || j == jstop
                    || board[i, j] != word[k])
                return false;
            
            board[i, j] = visited;
            if (++k == kstop || Dfs(i, j - 1) || Dfs(i, j + 1)
                             || Dfs(i - 1, j) || Dfs(i + 1, j))
                return true;
            
            board[i, j] = word[--k];
            return false;
        }
        
        for (var i = 0; i != istop; ++i) {
            for (var j = 0; j != jstop; ++j)
                if (Dfs(i, j)) return true;
        }
        return false;
    }
}