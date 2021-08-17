<Query Kind="FSharpProgram" />

let getln = System.Console.ReadLine

let pos n k =
    if k < n / 2 then 1 + k * 2 else (n - k - 1) * 2

for t = 1 to getln () |> int do
    let a = getln () |> (fun s -> s.Split ' ') |> Array.map int
    pos a.[0] a.[1] |> printfn "%d"
