<Query Kind="FSharpProgram" />

let s = System.Convert.ToString (System.Console.ReadLine () |> int, 2)
s.Split '0' |> Array.map String.length |> Array.max |> printfn "%d"
