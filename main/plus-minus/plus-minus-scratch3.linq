<Query Kind="FSharpProgram" />

open System

let n = Console.ReadLine () |> int
let a = Console.ReadLine () |> (fun s -> s.Split ' ') |> Array.map int
if Array.length a <> n then failwith "row not of specified length"
let groups = a |> Array.groupBy Math.Sign |> Array.sortBy fst

match groups |> Array.map (snd >> Array.length) with
    | [|n;z;p|] -> printfn "%A  %A  %A" n z p