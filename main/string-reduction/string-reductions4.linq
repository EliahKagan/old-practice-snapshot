<Query Kind="FSharpProgram" />

open System

let distinct str = 
    let rec dis skip acc (s:string) i n =
        if i = n then
            acc
        else
            let c = s.[i]
            if Set.contains c skip then
                dis skip acc s (i + 1) n
            else
                dis (Set.add c skip) (c::acc) s (i + 1) n
    
    String.length str |> dis Set.empty [] str 0 |> List.toArray |> Array.rev

Console.ReadLine () |> distinct |> Console.WriteLine
