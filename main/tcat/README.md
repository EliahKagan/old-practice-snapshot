# tcat - "trivial" cat-like programs

Programs to copy standard input to standard output, in D, C#, Scheme (Guile),
C++, and Perl. Some support some option processing and/or error reporting, so
they are not all actually *trivial*.

The comments are perhaps misleading, since **these programs *don't* work the
same as `cat`**, which doesn't know anything about lines. (`cat` behavior that
seems to copy input line by line is a result of terminal line
discipline--flushing the input buffer when a newline is entered--rather than
`cat`'s own logic.)
