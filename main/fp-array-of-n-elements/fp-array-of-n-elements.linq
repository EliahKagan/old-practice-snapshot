<Query Kind="FSharpProgram" />

open System

let f n =
    let rec loop acc = function
    | 0 -> acc
    | i -> loop (i::acc) (i - 1)
    
    loop [] n


let main() =
    let input = Console.ReadLine()
    let n = int input
    printfn "%d" (f n).Length

 
main()