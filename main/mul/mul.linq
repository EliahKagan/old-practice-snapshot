<Query Kind="FSharpProgram" />

let getln = System.Console.ReadLine

for i = 1 to getln () |> int do
    getln () |> (fun s -> s.Split ' ') |> Array.map bigint.Parse
             |> Array.reduce (*) |> System.Console.WriteLine
