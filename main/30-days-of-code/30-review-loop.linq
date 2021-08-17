<Query Kind="FSharpProgram" />

let funny str =
    let s = str |> Seq.map int |> Seq.toArray
    let r = Array.rev s
    
    Seq.forall (fun i -> abs (s.[i] - s.[i - 1]) = abs (r.[i] - r.[i - 1]))
               {1 .. Array.length s - 1}

let getln = System.Console.ReadLine

for t = 1 to getln () |> int do
    printfn "%s" (if getln () |> funny then "Funny" else "Not Funny")
