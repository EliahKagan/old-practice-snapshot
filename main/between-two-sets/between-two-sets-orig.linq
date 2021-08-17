<Query Kind="FSharpProgram" />

let rec gcd m = function
| 0 -> m
| n -> m % n |> gcd n

let lcm m n = m / gcd m n * n

let a, b =
    stdin.ReadLine () |> ignore

    let get () =
        stdin.ReadLine().Split ' ' |> Seq.map int |> Seq.sort |> Seq.toArray
    
    get (), get ()

let lo = a |> Array.reduce lcm
let hi = b |> Array.reduce gcd

{lo..lo..hi} |> Seq.filter (fun k -> hi % k = 0) |> Seq.length |> printfn "%d"