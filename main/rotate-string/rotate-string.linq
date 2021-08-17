<Query Kind="FSharpProgram" />

for t = 1 to System.Console.ReadLine () |> int do
    let s = System.Console.ReadLine ()
    let rot i = s.[i..] + s.[..(i - 1)]
    [1 .. String.length s] |> List.map rot |> String.concat " " |> printfn "%s"
