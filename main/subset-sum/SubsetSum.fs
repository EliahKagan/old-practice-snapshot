open System

let findFirstEqual (a : 'a array) i = // assumes a is sorted
    let rec find = function
    | 0                             -> 0
    | j when a.[j] <> a.[j - 1]     -> j
    | j                             -> find (j - 1)
    
    find i

let findFirstGreaterOrEqual (a : 'a array) (x : 'a) = // assumes a is sorted
    let i = Array.BinarySearch (a, x)
    
    if i < 0 then
        let j = ~~~i // insertion point
        if j = Array.length a then -1 else j
    else
        findFirstEqual a i

let readValue () = Console.ReadLine () |> int64

Console.ReadLine () |> ignore // don't need n

let sums =
    Console.ReadLine().Split()
    |> Seq.map int64
    |> Seq.sortDescending
    |> Seq.scan (+) 0L
    |> Seq.toArray

let t = Console.ReadLine () |> int

{1..t}
|> Seq.map (ignore >> readValue >> findFirstGreaterOrEqual sums)
|> Seq.iter (printfn "%d")
