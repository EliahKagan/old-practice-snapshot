<Query Kind="FSharpProgram" />

let n = System.Console.ReadLine () |> int
{1..10} |> Seq.iter (fun i -> n * i |> printfn "%d x %d = %d" n i)
