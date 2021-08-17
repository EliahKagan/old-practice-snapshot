<Query Kind="FSharpProgram" />

open System

let size = Console.ReadLine () |> int
let s = float size

let a = Console.ReadLine () |> (fun str -> str.Split ' ') |> Array.map int
if Array.length a <> size then failwith "row not of specified length"

let frac n = float (n - 1) / s

match a |> Array.append [|-1..1|]
        |> Array.groupBy Math.Sign
        |> Array.sortBy fst
        |> Array.map (snd >> Array.length) with
    | [|n;z;p|] -> [p;n;z] |> List.map frac |> List.iter (printfn "%f")
    | _ -> failwith "signum count array not of length 3"
