<Query Kind="FSharpProgram" />

let get () =
    let getln = System.Console.ReadLine
    let split (s:string) = s.Split ' '
    
    getln () |> ignore
    getln () |> split |> Array.map bigint.Parse |> Array.reduce (*)

let rec gcd a b = if b = 0I then a else a % b |> gcd b

gcd (get ()) (get ()) % 1000000007I |> printfn "%A"
