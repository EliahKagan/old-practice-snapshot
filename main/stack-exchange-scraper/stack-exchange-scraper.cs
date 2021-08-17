using System;
using System.IO;
using System.Text.RegularExpressions;

internal static class Solution {
    private static void Main()
    {
        // Matches the non-initial part of most tags (the attributes and ">").
        const string tagmidright = @"(?:[^<>""']*|""[^""]*""|'[^']*')*" + @">";

        // The prominently visible question hyperlink provides the title as
        // readable text, and the numeric question ID in the URL. This appears
        // at the beginning of a <div class="summary"> block.
        const string href = @"href=""/questions/(?<id>\d+)/[^""]+""";
        const string @class = @"class=""question-hyperlink""";
        const string start = @"<a\s+" + href + @"\s+" + @class + @"\s*>\s*";
        const string titleword = @"(?<titleword>[^<>\s]+)";
        const string title = titleword + @"(?:\s+" + titleword + @")*";
        const string end = @"\s*</a>";
        const string link = @"<h3>\s*" + start + title + end + @"\s*</h3>";
        const string top = @"<div\s+class=""summary""\s*>\s*" + link;

        // Some other tags and text, which should be skipped, follow.
        const string tagleft = @"<[a-z][a-z\d]*";
        const string tag = tagleft + @"(?!\s+class=""user-action-time"")"
                                   + tagmidright;
        const string middle = @"(?:[^<>]+|(?:" + tag + @"))*";

        // The time the question was asked or updated appears in a
        // <div class="user-action-time"> sub-block, inside a <span>.
        const string timeword = @"(?<timeword>[^<>\s]+)";
        const string time = timeword + @"(?:\s+" + timeword + @")*";
        const string bottom = @"<div\s+class=""user-action-time""\s*>\s*\w+\s*"
                            + @"<span\s+" + tagmidright + time
                            + @"</span>\s*</div>";

        const string pattern = "(?i)" + top + middle + bottom;
    }
}
