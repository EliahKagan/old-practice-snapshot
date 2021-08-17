<Query Kind="FSharpProgram" />

[<Literal>]
let M = 1000000007L

let rec pow n = function
| 0L -> 1L
| p  ->
    let r = pow n (p / 2L)
    let s = r * r % M
    if p % 2L = 0L then s else s * n % M

pow 2L 20L |> printfn "%d"