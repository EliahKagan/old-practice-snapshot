<Query Kind="FSharpProgram" />

let insertionSort (a : int array) = // returns total number of shifts
    let insert j =
        let e = a.[j]
    
        let rec ins acc j =
            if j <> 0 && e < a.[j - 1] then
                a.[j] <- a.[j - 1]
                ins (acc + 1) (j - 1)
            else
                a.[j] <- e
                acc
        
        ins 0 j
    
    {1..(Array.length a - 1)} |> Seq.sumBy insert

stdin.ReadLine () |> ignore
stdin.ReadLine().Split ' ' |> Array.map int |> insertionSort |> printfn "%d"