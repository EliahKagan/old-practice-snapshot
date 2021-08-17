<Query Kind="FSharpProgram" />

open System

let size = Console.ReadLine () |> int
let a = Console.ReadLine () |> (fun str -> str.Split ' ') |> Array.map int
if Array.length a <> size then failwith "row not of specified length"

let s = float size
let groups = a |> Array.groupBy Math.Sign |> Array.sortBy fst

match groups |> Array.map (snd >> Array.length) with
    | [|n;z;p|] ->
        [p;n;z] |> List.map (fun k -> float k / s) |> List.iter (printfn "%f")