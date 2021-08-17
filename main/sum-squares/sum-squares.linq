<Query Kind="FSharpProgram" />

let get = System.Console.ReadLine >> int
let a, b = get (), get ()
[a..b] |> List.sumBy (fun x -> x * x) |> printfn "%d"