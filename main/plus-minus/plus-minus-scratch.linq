<Query Kind="FSharpProgram" />

open System

let n = Console.ReadLine () |> int
let a = Console.ReadLine () |> (fun s -> s.Split ' ') |> Array.map int
if Array.length a <> n then failwith "row not of specified length"

match a |> Array.groupBy Math.Sign |> Array.sortBy fst |> Array.map snd with
    | [|n;z;p|] -> printfn "%A  %A  %A" n z p