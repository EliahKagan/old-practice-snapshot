<Query Kind="FSharpProgram" />

open System

let d = 100

let get () =
    Console.ReadLine () |> ignore
    Console.ReadLine () |> (fun s -> s.Split ' ') |> Array.map int

let a, b = get (), get ()
let imin = Array.min b

let normal = Array.map (fun i -> i - imin)
let denormal = Seq.map (fun i -> i + imin)

let counts:int[] = d + 1 |> Array.zeroCreate
b |> normal |> Array.iter (fun i -> counts.[i] <- counts.[i] + 1)
a |> normal |> Array.iter (fun i -> counts.[i] <- counts.[i] - 1)

{0..d} |> Seq.filter (fun i -> counts.[i] > 0) |> denormal
       |> Seq.map string |> String.concat " " |> printfn "%s"
