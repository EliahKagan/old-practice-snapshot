let sumOfSquares n = [1..n] |> List.map (fun i -> i * i) |> List.sum
sumOfSquares 100 |> printfn "%d"
