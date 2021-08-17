<Query Kind="FSharpProgram" />

let getln = System.Console.ReadLine

let n = getln () |> int
let a = getln () |> (fun s -> s.Split ' ') |> Array.map int
let f = Array.concat [ [|-1|]; a]

Seq.iter (fun i -> printfn "%d" f.[f.[i]]) {1..n}
