<Query Kind="FSharpProgram" />

let getln = System.Console.ReadLine

getln () |> ignore // don't need n

getln().Split ' '
|> Seq.groupBy int
|> Seq.map (snd >> Seq.length)
|> Seq.sortDescending
|> Seq.skip 1
|> Seq.sum
|> printfn "%d"