<Query Kind="FSharpExpression" />

let n = 10
let s = "beabeefeab"

let tlen ch1 ch2 =
    let rec sublen acc a b i =
        if i = n then
            acc
        else
            let c = s.[i]
            
            if c = a then       i + 1 |> sublen (acc + 1) b a
            elif c = b then     0
            else                i + 1 |> sublen acc a b

    if ch1 = ch2 then
        0
    else
        match sublen 0 ch1 ch2 0 with
        | 1     -> 0    // a t-string cannot be a single character
        | len   -> len

tlen 'a' 'f'