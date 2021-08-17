# read-hackerrank-input

This was a sketch of an input routine for reading whitespace-separated records
in the form HackerRank problems often supplies numeric inputs, where the number
of expected fields appears followed by a newline, the expected fields separated
by horizontal whitespace, and then either another newline or end-of-file.

The approach to parsig that I used here was strict or, to put it less
positively, brittle. If I recall correctly, I wanted to validate the input data
while reading it, so if expected data were not read (either due to a coding
mistake of mine or due to a malformed test case or example input), the program
would fail fast.

**I rarely ended up using this.** I think I recall that techniques like this
failed too often, and I never actually caught a bug or bad test case this way.
Rather than reading a line and parsing fields from it after doing so, it is
sufficient, and enormously simpler, to read the expected number of fields
(treating newlines the same as other whitespace).
