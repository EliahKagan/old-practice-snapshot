<Query Kind="FSharpProgram" />

let rec (^^) n = function
    | 0 -> 1I
    | 1 -> n
    | p ->
        let r = n ^^ (p / 2)
        let s = r * r
        if p % 2 = 0 then s else s * n

17I^^300 |> printfn "%A" // my bigint->int->bigint power operator (above)
17I**300 |> printfn "%A" // regular bigint->int->bigint power operator
