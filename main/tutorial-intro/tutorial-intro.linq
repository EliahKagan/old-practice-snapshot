<Query Kind="FSharpProgram" />

let bsearch (a : 'a array) key =
    let rec bs low high =
        if high < low then
            None
        else
            let mid = low + (high - low) / 2
            
            if      a.[mid] < key then  bs (mid + 1) high
            elif    a.[mid] > key then  bs low (mid - 1)
            else                        Some(mid)
    
    Array.length a - 1 |> bs 0

let key = stdin.ReadLine () |> int
stdin.ReadLine () |> ignore
let a = stdin.ReadLine().Split ' ' |> Array.map int

match bsearch a key with
| Some(i)   -> printfn "%d" i
| None      -> failwith "element not found"