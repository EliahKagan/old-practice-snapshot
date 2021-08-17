<Query Kind="FSharpProgram" />

let factorial n = Seq.fold (*) 1I {2I..n}
System.Console.ReadLine () |> bigint.Parse |> factorial |> printfn "%A"
