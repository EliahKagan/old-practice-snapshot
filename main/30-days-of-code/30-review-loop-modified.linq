<Query Kind="FSharpProgram" />

open System

for i = 1 to Console.ReadLine () |> int do
    let s = Console.ReadLine ()
    let n = String.length s - 1
    let put i = Console.Write s.[i]
    
    Seq.iter put {0..2..n}
    Console.Write ' '
    Seq.iter put {1..2..n}
    Console.WriteLine ()
