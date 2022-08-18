# old-practice-snapshot - a bunch of old solutions to coding exercises

*My recent solutions are in a different repository,
[**practice**](https://github.com/EliahKagan/practice). You might be looking
for that.*

This is a snapshot, without useful source control history, of my **old
solutions** to coding and algorithms exercises (practice problems / competitive
programming problems). Most are for problems posed on websites and checked with
an online judge, but I&rsquo;ve also included a small handful of personal
exercises and exercises from books, when they seemed worth including and not
better in any other repository.

I wrote and saved these solutions originally without source control. 😬 (The
directory tree was also almost completely flat.) That was a mistake... but one
that can be partially rectified, because I kept backup files with a systematic
naming scheme--well, a few such schemes--and the [file modification timestamps
are correct](#when-things-are-from), which means it is possible to
automatically generate a repository in which every version of every file has a
commit, the sequence and dates that everything was written are reflected, and
numerous files have useful histories (so `git blame` would often be useful,
etc.). This is to say that it is possible to turn a disadvantage into an
advantage.

**But *this* is not the repository that turns that disadvantage into and
advantage!** No, this is just a snapshot of the whole directory tree in a
single commit. It is far less useful than the proper history-bearing repository
will be once I get around to making it, but perhaps not totally useless. It's
at least useful to me.

This repository does not include recent solutions, which are in the
[**practice**](https://github.com/EliahKagan/practice) repository instead and
not here. That is to say that this repository, old-practice-snapshot, is a
snapshot of old-practice, *not* an old snapshot of practice. Some problems have
solutions in both repositories, but solutions in the practice repository are
not based on solutions here, and often used different techniques or were
otherwise implemented in substantially different ways (though this is not
always the case). There are also many problems here that have no solutions
there, and many problems there that have no solutions here.

## License

This repository is licensed under [0BSD](https://spdx.org/licenses/0BSD.html).
See [**`LICENSE`**](LICENSE).

Some material in this repository is not written by me; for example, problems
sometimes contain scaffolding code written by problem setters, and I've
included some small input test cases. I've only included any material not
written by me when I believe it is clearly fair use. See
[`FAIR-USE.md`](FAIR-USE.md) for details.

## Where things are

Most code in this repository is in the `main` directory. This includes
solutions to numerous HackerRank, Geeksforgeeks, and LeetCode problems, as well
as occasional problems from other websites and sources, and some personal
practice problems.

Several things are better organized and in the `hier` directory, because it
follows a hierarchical organization scheme.

Code that is not for a specific problem but is relevant to multiple problems,
such as Sieve of Eratosthenes implementations written and tested by themselves
and then adapted to various problems, is in `meta`.

## When things are from

Most of the solutions in this repository were written from 2016 to 2018,
heavily tapering off in 2019, though it contains a small amount of code from
2013, 2015, and 2020. This repository does have content from 2021, but it
consists almost entirely of README files and other additions connected to
organizing it and presenting its contents.

```text
$ find . -type f \! -name '.*' -printf '%TY\n' | sort | uniq -c
     16 2013
     20 2015
   1606 2016
   1362 2017
   1592 2018
    356 2019
     45 2020
     38 2021
```

The file timestamps (on regular files, not directories) are correct, but `git`
doesn't retain those automatically. The eventual solution will be to build a
repository, as described above. For this snapshot, I've simply included a 7-zip
archive file, `old-practice-snapshot.7z`, in the root of the repository.
Although there are far more compact alternatives--such as generating a script
that, when run, restores the timestamps--an archive of the files is simple to
include and easy to use, and the increase in size is not severe.
