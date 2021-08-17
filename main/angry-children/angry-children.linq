<Query Kind="FSharpProgram" />

let get = System.Console.ReadLine >> int

let n, k = get (), get ()
let a = Array.init n (ignore >> get) |> Array.sort

let delta = k - 1
let min = {0 .. n - k} |> Seq.map (fun i -> a.[i + delta] - a.[i]) |> Seq.min
printfn "%d" min
