let greet n = List.map (fun x -> printfn "Hello World") [1..n]
System.Console.ReadLine () |> int |> greet |> ignore
