<Query Kind="FSharpProgram" />

let n = System.Console.ReadLine () |> int
let s = if n % 2 <> 0 || (6 <= n && n <= 20) then "Weird" else "Not Weird"
printfn "%s" s
