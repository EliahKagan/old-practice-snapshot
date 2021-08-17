<Query Kind="FSharpProgram" />

let get () = System.Console.ReadLine () |> int
get () + get () |> printfn "%d"