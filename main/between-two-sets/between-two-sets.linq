<Query Kind="FSharpProgram" />

let rec gcd m = function
| 0 -> m
| n -> m % n |> gcd n

let lcm m n = m / gcd m n * n

let getBound reducer =
    stdin.ReadLine().Split ' '
    |> Seq.map int
    |> Seq.sort
    |> Seq.reduce reducer

stdin.ReadLine () |> ignore
let lower = getBound lcm
let upper = getBound gcd

{lower..lower..upper}
|> Seq.filter (fun k -> upper % k = 0)
|> Seq.length
|> printfn "%d"