open System

let maxconj n k =
    let mutable m = 0
    for a = 1 to n - 1 do
        for b = a + 1 to n do
            let ab = a &&& b
            if m < ab && ab < k then m <- ab
    m

for t = 1 to Console.ReadLine () |> int do
    let nk = Console.ReadLine () |> (fun s -> s.Split ' ') |> Array.map int
    maxconj nk.[0] nk.[1] |> Console.WriteLine
