<Query Kind="FSharpProgram" />

let factorial n = Seq.reduce (*) {1..n}
System.Console.ReadLine () |> int |> factorial |> printfn "%d"
