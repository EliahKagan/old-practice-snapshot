<Query Kind="FSharpProgram" />

let getln = System.Console.ReadLine

let n = getln () |> int
let a = getln () |> (fun s -> s.Split ' ') |> Array.map int
let f = Array.concat [ [|-1|]; a ]

{1..n} |> Seq.iter (fun i -> f.[f.[i]] |> printfn "%d")
