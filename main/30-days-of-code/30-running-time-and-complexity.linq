<Query Kind="FSharpProgram" />

let prime n =
    let isqrt = float >> sqrt >> floor >> int
    n > 1 && Seq.forall (fun i -> n % i <> 0) {2 .. isqrt n}

let get = System.Console.ReadLine >> int

for t = 1 to get () do
    printfn "%s" (if get () |> prime then "Prime" else "Not prime")
