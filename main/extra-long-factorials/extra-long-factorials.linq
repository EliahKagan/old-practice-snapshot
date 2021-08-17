<Query Kind="FSharpProgram" />

let rec factorial n = if n < 2I then 1I else n * factorial (n - 1I)
System.Console.ReadLine () |> bigint.Parse |> factorial |> printfn "%A"
