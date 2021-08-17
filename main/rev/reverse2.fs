let rec readToFront xs =
    match System.Console.ReadLine () with
        | null -> xs
        | line -> (int line)::xs |> readToFront

readToFront [] |> List.iter (printfn "%d")
