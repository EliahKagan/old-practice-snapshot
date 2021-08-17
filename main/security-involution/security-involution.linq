<Query Kind="FSharpProgram" />

let getln = System.Console.ReadLine

let n = getln () |> int
let a = getln () |> (fun s -> s.Split ' ') |> Array.map int
let f = Array.concat [ [|-1|]; a ]

let invol = List.map (fun i -> f.[f.[i]]) [1..n] = [1..n]
printfn "%s" (if invol then "YES" else "NO")
