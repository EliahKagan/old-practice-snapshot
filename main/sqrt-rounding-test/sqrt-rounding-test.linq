<Query Kind="FSharpProgram" />

let inline sq i = i * i

let isqrtu = float >> sqrt >> ceil >> int
let isqrtl = float >> sqrt >> floor >> int

let peculiar i =
    let high, low = isqrtu i, isqrtl i
    if high = low then sq high <> i else sq high = i || sq low = i

{1..100000000} |> Seq.filter peculiar |> printfn "%A"
