<Query Kind="FSharpProgram" />

open System

let conjRange a b =
    let inline prop i n = n ||| (n >>> i)
    let mask = prop 1 >> prop 2 >> prop 4 >> prop 8 >> prop 16
    a &&& ~~~(a ^^^ b |> mask)

for i = 1 to Console.ReadLine () |> int do
    let ab = Console.ReadLine () |> (fun s -> s.Split ' ') |> Array.map uint32
    conjRange ab.[0] ab.[1] |> Console.WriteLine
