<Query Kind="FSharpProgram" />

open System

let check n = if 0 <= n && n <= 5 then n else failwith "input out of range"

let rec grow x y d = function
    | 0 -> []
    | n -> ([1..d] |> List.map (fun i -> x, y + i))
            ::([1..d] |> List.map (fun i -> x - i, y + d + i))
            ::([1..d] |> List.map (fun i -> x + i, y + d + i))
            ::(grow (x - d) (y + d * 2) (d / 2) (n - 1)
                @ grow (x + d) (y + d * 2) (d / 2) (n - 1))

let getTree = check >> grow 49 -1 16 >> List.concat >> List.groupBy snd // by y
                    >> List.map (fun g -> fst g, snd g |> List.map fst) // y,xs

let getRow t y = match t |> List.tryFind (fun g -> fst g = y) with
                    | Some (_,xs) -> xs
                    | None -> []

let getAllRows t = [62..-1..0] |> List.map (getRow t)

let drawRow xs =
    let getElement i = if xs |> List.contains i then '1' else '_'
    [|0..99|] |> Array.map getElement |> Console.WriteLine

Console.ReadLine () |> int |> getTree |> getAllRows |> List.iter drawRow
