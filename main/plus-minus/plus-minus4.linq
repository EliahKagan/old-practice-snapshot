<Query Kind="FSharpProgram" />

open System

let n = Console.ReadLine () |> float

let bins = Console.ReadLine () |> (fun s -> s.Split ' ') |> Array.toList
                               |> List.groupBy (int >> Math.Sign)

let frac sign = bins |> List.filter (fst >> ((=) sign)) |> List.collect snd
                     |> List.length |> float |> (fun x -> x / n)

[1;-1;0] |> List.map frac |> List.iter (printfn "%f")
