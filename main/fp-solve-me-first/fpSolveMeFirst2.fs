let getval () = System.Console.ReadLine() |> int
getval () + getval () |> printfn "%d"
