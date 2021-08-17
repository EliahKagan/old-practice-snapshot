<Query Kind="FSharpProgram" />

let getln = System.Console.ReadLine

let n = getln () |> int
let fn = (getln ()).Split ' ' |> Array.mapi (fun i s -> int s, i + 1) |> Map

Seq.iter (fun i -> printfn "%d" fn.[i]) {1..n}
