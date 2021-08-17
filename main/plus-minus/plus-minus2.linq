<Query Kind="FSharpProgram" />

let getln () = System.Console.ReadLine ()

let n = getln () |> int
let s = float n
let a = getln () |> (fun s -> s.Split ' ') |> Array.take n |> Array.map int

let count pred = a |> Array.filter pred |> Array.length
let putFrac pred = float (count pred) / s |> printfn "%f"
[(<) 0; (>) 0; (=) 0] |> List.iter putFrac
