<Query Kind="FSharpProgram" />

let conjRange a b =
    let inline prop i n = n ||| (n >>> i)
    let mask = prop 1 >> prop 2 >> prop 4 >> prop 8 >> prop 16
    a &&& ~~~(a ^^^ b |> mask)

let inline conjRangeSlow a b = Seq.reduce (&&&) {a..b}

let conjRangeTest n =
    let test a = Seq.forall (fun b -> conjRange a b = conjRangeSlow a b) {a..n}
    Seq.forall test {0u..n}

conjRangeTest 1024u |> printfn "%A"
