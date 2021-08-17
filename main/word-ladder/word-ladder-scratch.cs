#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Text;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

public class Solution {
    public int LadderLength(string beginWord, string endWord,
                            IList<string> wordList)
    {
        Contract.Assert(beginWord != endWord);

        var set = new HashSet<string>(wordList);
        if (!set.Contains(endWord)) return NoPath;
        set.Remove(beginWord);

        var queue = new Queue<string>();
        queue.Enqueue(beginWord);

        for (var level = 2; queue.Count != 0; ++level) {
            for (var breadth = queue.Count; breadth != 0; --breadth) {
                var word = new StringBuilder(queue.Dequeue());

                for (var i = 0; i != word.Length; ++i) {
                    var oldChar = word[i];

                    for (var newChar = 'a'; newChar <= 'z'; ++newChar) {
                        if (oldChar == newChar) continue;

                        word[i] = newChar;
                        var frozenWord = word.ToString();
                        if (!set.Contains(frozenWord)) continue;

                        set.Remove(frozenWord);
                        if (frozenWord == endWord) return level;
                        queue.Enqueue(frozenWord);
                    }

                    word[i] = oldChar;
                }
            }
        }

        return NoPath;
    }

    private const int NoPath = 0;
}

internal class UnitTest {
    private static void Main()
    {
        var s = new Solution();

        var ans = s.LadderLength(
                    "hit", "cog",
                    new[] { "hot", "dot", "dog", "lot", "log", "cog" });

        Console.WriteLine(ans);
    }
}
