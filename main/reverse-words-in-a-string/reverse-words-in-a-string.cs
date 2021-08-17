public class Solution {
    private static char[] Space = { ' ' };

    public string ReverseWords(string s)
        => string.Join(" ", s.Split(Space, StringSplitOptions.RemoveEmptyEntries).Reverse());
}
