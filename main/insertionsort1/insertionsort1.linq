<Query Kind="FSharpProgram" />

let insert a =
    let print () =
        a |> Seq.map (sprintf "%d") |> String.concat " " |> printfn "%s"
    
    let jmax = Array.length a - 1
    let e = a.[jmax]
    
    let rec ins j =
        if j <> 0 && e < a.[j - 1] then
            a.[j] <- a.[j - 1]
            print ()
            j - 1 |> ins
        else
            a.[j] <- e
            print ()
    
    ins jmax

stdin.ReadLine () |> ignore
stdin.ReadLine().Split ' ' |> Array.map int |> insert