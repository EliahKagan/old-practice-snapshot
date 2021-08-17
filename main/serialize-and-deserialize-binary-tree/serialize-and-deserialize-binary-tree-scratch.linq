<Query Kind="Statements" />

var sb = new StringBuilder();
foreach (var s in new[] { "abc", "de", "fgh" }) {
    sb.Append(s);
    sb.Append(';');
}
sb.Length -= 1;
sb.Dump();

var data = "";
var reprs = Array.ConvertAll(data.Split(';'), tok => tok.Split(','));
reprs.Dump();

"".Split(';')[0].Length.Dump();
