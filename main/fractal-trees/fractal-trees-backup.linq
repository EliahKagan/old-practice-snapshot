<Query Kind="FSharpProgram" />

open System

let rec grow x y d = function
    | 0 -> []
    | n -> ([1..d] |> List.map (fun i -> x, y + i))
            ::([1..d] |> List.map (fun i -> x - i, y + d + i))
            ::([1..d] |> List.map (fun i -> x + i, y + d + i))
            ::(grow (x - d) (y + d * 2) (d / 2) (n - 1)
                @ grow (x + d) (y + d * 2) (d / 2) (n - 1))

let check n = if 0 <= n && n <= 5 then n else failwith "input out of range"

let tree = check >> grow 49 -1 16 >> List.concat >> List.groupBy snd // by y
                 >> List.map (fun g -> fst g, snd g |> List.map fst) // y, xs

let checkLocation t x y =
    t |> List.exists (fun g -> fst g = y && snd g |> List.contains x)

let getElement t x y = if checkLocation t x y then '1' else '_'

let drawRow t y = [|0..99|] |> Array.map (fun i -> 

Console.ReadLine () |> int |> tree |> Dump