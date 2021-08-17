<Query Kind="FSharpProgram" />

let getln = System.Console.ReadLine

let id = [| 1 .. getln () |> int |]
let fn = getln () |> (fun s -> s.Split ' ') |> Array.map int

printfn "%s" (if Array.sort fn = id then "YES" else "NO")
