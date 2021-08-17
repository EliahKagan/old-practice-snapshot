<Query Kind="FSharpProgram" />

let harmonic p = {p .. -1 .. 1} |> Seq.sumBy (fun k -> 1. / float k)

let a = System.Console.ReadLine () |> (fun s -> s.Split ' ') |> Array.map int
let p = a |> Array.reduce (*)

float p * harmonic p |> printfn "%f"
