// tcat.d - simple cat-like program (copies files line-by-line to stdout)

import std.exception, std.stdio;

enum Status { success, failureIO, failureSyntax };

void cat(File f)
{
    foreach (const line; f.byLine()) writeln(line);
}

int main(string[] args)
{
    if (args.length <= 1) {
        cat(stdin);
        return Status.success;
    }

    bool err = false, doOpts = true, noFiles = true;
    foreach (immutable path; args[1 .. $]) {
        if (path.length == 0) continue;

        if (doOpts) {
            switch (path) {
            case "--":
                doOpts = false;
                continue;

            case "-":
                cat(stdin);
                noFiles = false;
                continue;

            default:
                if (path[0] == '-') {
                    stderr.writefln("unrecognized option \"%s\"", path);
                    return Status.failureSyntax;
                }
            }
        }

        try {
            cat(File(path, "r"));
            noFiles = false;
        }
        catch (ErrnoException e) {
            stderr.writefln("error: can't open \"%s\"", path);
            err = true;
        }
    }

    return err ? Status.failureIO : Status.success;
}
