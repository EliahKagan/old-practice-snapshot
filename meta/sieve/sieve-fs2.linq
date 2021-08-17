<Query Kind="FSharpProgram" />

// Returns the set of primes up to n.
let sieve n =
    let (a : bool array) = n + 1 |> Array.zeroCreate // true = marked composite
    
    for i in {3..2..(n |> float |> sqrt |> int)} do
        if not a.[i] then
            for j in {(i * i)..(i * 2)..n} do a.[j] <- true
    
    {3..2..n} |> Seq.filter (fun i -> not a.[i]) |> Seq.append [2] |> set

sieve 5000 |> Dump |> ignore