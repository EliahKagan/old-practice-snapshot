open System

let rec permute = function
    | y::x::xs -> x::y::(permute xs)
    | _ -> []

for i = 1 to Console.ReadLine () |> int do
    let s = Console.ReadLine ()
    let t = s |> Seq.toList |> permute |> List.toArray |> String
    Console.WriteLine t
