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

let imperativeSieve n = // Returns the set of primes up to n. (Traditional.)
    let (a : bool array) = n + 1 |> Array.zeroCreate // true => composite
    
    for i in {3..2..(isqrt n)} do
        if not a.[i] then
            for j in {(i * i)..(i * 2)..n} do a.[j] <- true
    
    {3..2..n} |> Seq.filter (fun i -> not a.[i]) |> Seq.append [2] |> set

let dump x = x |> Dump |> ignore

let s = primes 1000000
let t = imperativeSieve 1000000
s = t |> dump
s |> dump