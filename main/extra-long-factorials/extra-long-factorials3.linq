<Query Kind="FSharpProgram" />

let factorial n = Seq.reduce (*) {1I..n}
System.Console.ReadLine () |> bigint.Parse |> factorial |> printfn "%A"
