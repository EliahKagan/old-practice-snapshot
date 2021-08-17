// tcat0.d - trivial cat-like program (copies files line-by-line to stdout)

import std.stdio;

void main(string[] args)
{
    foreach (immutable path; args[1 .. $]) {
        foreach (const line; File(path, "r").byLine()) writeln(line);
    }
}
