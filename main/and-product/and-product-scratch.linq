<Query Kind="FSharpProgram" />

let flp2 (n:uint32) =    // obtains the leftmost bit of n
    let inline prop i k = k ||| (k >>> i)
    let filled = n |> prop 1 |> prop 2 |> prop 4 |> prop 8 |> prop 16
    filled - (filled >>> 1)

let conjRange a b =
    let x = a ^^^ b |> flp2
    
    let rec conj acc bit =
        if bit = x then acc else conj (acc ||| (a &&& bit)) (bit >>> 1)
    
    a ||| b |> flp2 |> conj 0u

let inline conjRangeSlow a b = Seq.reduce (&&&) {a..b}

let conjRangeTest n =
    let test a = Seq.forall (fun b -> conjRange a b = conjRangeSlow a b) {a..n}
    Seq.forall test {0u..n}

conjRangeTest 1024u |> printfn "%A"
