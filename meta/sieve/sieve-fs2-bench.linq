<Query Kind="FSharpProgram" />

let isqrt n = n |> float |> sqrt |> int // precise on 32-bit ints

let imperativeSieve n = // Returns the set of primes up to n. (Traditional.)
    let (a : bool array) = n + 1 |> Array.zeroCreate // true => composite
    
    for i in {3..2..(isqrt n)} do
        if not a.[i] then
            for j in {(i * i)..(i * 2)..n} do a.[j] <- true
    
    {3..2..n} |> Seq.filter (fun i -> not a.[i]) |> Seq.append [2] |> set

imperativeSieve 1000000 |> ignore