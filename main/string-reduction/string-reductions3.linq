<Query Kind="FSharpProgram" />

open System

let distinct items =
    let rec dis skip acc = function
        | [] -> acc
        | x::xs ->
            if skip |> Set.contains x then xs |> dis skip acc
                                      else xs |> dis (Set.add x skip) (x::acc)
    
    items |> dis Set.empty [] |> List.rev

let reduced = Console.ReadLine () |> Seq.toList |> distinct
reduced |> List.toArray |> Console.WriteLine
