<Query Kind="FSharpProgram" />

let getln = System.Console.ReadLine

let n = getln () |> int
let fn = (getln ()).Split ' ' |> Array.mapi (fun i s -> int s, i + 1) |> Map
{1..n} |> Seq.map (fun i -> string fn.[i]) |> String.concat " " |> printfn "%s"
