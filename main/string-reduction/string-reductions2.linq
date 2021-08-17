<Query Kind="FSharpProgram" />

open System

let distinct items =
    let rec dis skip acc = function
        | x::xs when skip |> Set.contains x -> xs |> dis skip acc
        | x::xs -> xs |> dis (Set.add x skip) (x::acc)
        | [] -> acc
    
    items |> dis Set.empty [] |> List.rev

let reduced = Console.ReadLine () |> Seq.toList |> distinct
reduced |> List.toArray |> Console.WriteLine
