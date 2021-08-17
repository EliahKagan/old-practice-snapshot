<Query Kind="FSharpProgram" />

open System

let distinct items =
    let rec dis acc = function
        | [] -> acc
        | x::xs -> xs |> dis (if List.contains x acc then acc else x::acc)
    
    items |> dis [] |> List.rev

let reduced = Console.ReadLine () |> Seq.toList |> distinct
reduced |> List.toArray |> Console.WriteLine
