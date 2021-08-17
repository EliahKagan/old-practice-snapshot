public class Solution {
    private static string[] Letters = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    public IList<string> LetterCombinations(string digits) {
        var allPaths = new List<string>();
        if (digits.Length == 0) return allPaths;

        // Here, digits.Length > 0, so the capacity is valid.
        var path = new StringBuilder(digits.Length, digits.Length);

        void Dfs(int i) {
            if (i == digits.Length) {
                allPaths.Add(path.ToString());
                return;
            }

            foreach (var ch in Letters[digits[i] - '0']) {
                path.Append(ch);
                Dfs(i + 1);
                path.Remove(i, 1);
            }
        }

        Dfs(0);
        return allPaths;
    }
}
