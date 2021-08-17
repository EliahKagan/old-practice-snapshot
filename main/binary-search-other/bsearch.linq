<Query Kind="FSharpProgram" />

let failIfNone msg = function
| Some(x)   -> x
| None      -> failwith msg

let bsearch (a : 'a array) key =
    let rec bs low high =
        if high < low then
            None
        else
            let mid = low + (high - low) / 2 |> Dump
            
            if      a.[mid] < key then  bs (mid + 1) high
            elif    a.[mid] > key then  bs low (mid - 1)
            else                        Some(mid)
    
    Array.length a - 1 |> bs 0

let key = 14

bsearch [|1..1000|] key
|> failIfNone (sprintf "Key %d not found!" key)
|> printfn "Found key %d at index %A." key