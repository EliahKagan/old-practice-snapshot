<Query Kind="FSharpProgram" />

[<Literal>]
let M = 1000000007L

let rec pow n = function
| 0L -> 1L
| p  ->
    let r = pow n (p / 2L)
    let s = r * r % M
    if p % 2L = 0L then s else s * n % M

let a, b, t =
    let abt = System.Console.ReadLine().Split() |> Array.map int64
    abt.[0], abt.[1], abt.[2]

pow ((a + b) / 2L) t |> printfn "%d"
