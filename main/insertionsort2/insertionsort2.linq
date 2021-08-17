<Query Kind="FSharpProgram" />

let insertionSort (a : int array) =
    let insert j =
        let e = a.[j]
    
        let rec ins j =
            if j <> 0 && e < a.[j - 1] then
                a.[j] <- a.[j - 1]
                j - 1 |> ins
            else
                a.[j] <- e
        
        ins j
        a |> Seq.map (sprintf "%d") |> String.concat " " |> printfn "%s"
    
    {1..(Array.length a - 1)} |> Seq.iter insert

stdin.ReadLine () |> ignore
stdin.ReadLine().Split ' ' |> Array.map int |> insertionSort