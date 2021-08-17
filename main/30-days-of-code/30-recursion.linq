<Query Kind="FSharpProgram" />

let rec factorial = function
    | 0 -> 1
    | n -> n * factorial (n - 1)

System.Console.ReadLine () |> int |> factorial |> printfn "%d"
