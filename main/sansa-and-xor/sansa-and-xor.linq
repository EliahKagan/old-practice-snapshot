<Query Kind="FSharpProgram" />

open System

let getOne = Console.ReadLine >> int

for t = 1 to getOne () do
    let n = getOne ()
    let a = Console.ReadLine () |> (fun s -> s.Split ' ') |> Array.map int
    
    let ans =
        if n % 2 = 0 then
            0
        else
            {0..2..n} |> Seq.map (Array.get a) |> Seq.reduce (^^^)
    
    printfn "%d" ans
