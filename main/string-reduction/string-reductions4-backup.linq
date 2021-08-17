<Query Kind="FSharpProgram" />

open System

let distinct str =
    let rec dis skip acc (s:string) = function
        | 0 -> acc
        | n ->
            let i = n - 1
            let c = s.[i]
            
            if Set.contains c skip then dis skip acc s i
                                   else dis (Set.add c skip) (c::acc) s i
    
    String.length str |> dis Set.empty [] str

Console.ReadLine () |> distinct |> List.toArray |> Console.WriteLine
