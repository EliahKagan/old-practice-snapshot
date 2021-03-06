<Query Kind="FSharpProgram" />

let isqrt n = n |> float |> sqrt |> int // precise on 32-bit ints

let primes n = // Returns the set of primes up to n. (Functional, eager.)
    let imin, imax = 3, isqrt n

    let rec sieve i cur =
        if i > imax then
            cur
        else
            let next =
                if cur |> Set.contains i then
                    cur - set {(i * i)..(i * 2)..n}
                else
                    cur

            sieve (i + 2) next

    {imin..2..n} |> Seq.append [2] |> set |> sieve imin

primes 1000000 |> ignore