<Query Kind="FSharpProgram" />

open System

let n = Console.ReadLine () |> int
let s = float n

let record = Console.ReadLine () |> (fun s -> s.Split ' ')
let values = record |> Array.toList |> List.take n |> List.map int

let pnzFractions =
    let rec pnz p n z = function
        | [] -> [p;n;z]
        | (x:int)::xs ->
            match Math.Sign x with
                | 1 -> pnz (p + 1) n z xs
                | -1 -> pnz p (n + 1) z xs
                | _ -> pnz p n (z + 1) xs
    
    pnz 0 0 0 >> List.map (fun k -> float k / s)

pnzFractions values |> List.iter (printfn "%f")
