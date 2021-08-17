<Query Kind="FSharpProgram" />

let factorial =
    let rec fac p n = if n < 2I then p else fac (p * n) (n - 1I)
    fac 1I

System.Console.ReadLine () |> bigint.Parse |> factorial |> printfn "%A"
