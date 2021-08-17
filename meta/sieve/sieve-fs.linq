<Query Kind="FSharpProgram" />

let sieve n =
    // false means not (yet?) marked as composite
    let (a : bool array) = n + 1 |> Array.zeroCreate
    
    for i in {3..2..(n |> float |> sqrt |> int)} do
        match a.[i] with
        | true ->   ()
        | false ->  for j in {(i * i)..(i * 2)..n} do a.[j] <- true
    
    {3..2..n} |> Seq.filter (fun i -> not a.[i]) |> Seq.append [2] |> set

sieve 5000 |> Dump |> ignore