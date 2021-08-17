<Query Kind="Statements" />

const int t = 10;
const int n = 100000;

Directory.SetCurrentDirectory(@"C:\Users\ek\source");

using (var stream = File.CreateText("alternating-characters.in")) {
    stream.WriteLine(t);
    foreach (var i in Enumerable.Range(1, t)) {
        foreach (var j in Enumerable.Range(1, n)) stream.Write('A');
        stream.WriteLine();
    }
}
