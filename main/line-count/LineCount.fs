let countLines () =
    let rec count acc =
        match System.Console.ReadLine () with
        | null  -> acc
        | _     -> acc + 1 |> count
    
    count 0

countLines () |> printfn "%d"
