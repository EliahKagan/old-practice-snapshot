<Query Kind="FSharpProgram" />

open System

let rec fibModified a b n =
    if n < 3 then
        b
    else
        fibModified b (a + b**2) (n - 1)

let readRecord () =
    Console.ReadLine().Split(Unchecked.defaultof<char[]>,
                             StringSplitOptions.RemoveEmptyEntries)
    |> Array.map int

[<EntryPoint>]
let main argv =
    match readRecord () with
        | [|a; b; n|] ->
            fibModified (bigint a) (bigint b) n |> printfn "%A"
            0
        | _ ->
            failwith "wrong record length"
