<Query Kind="FSharpProgram" />

let sort (a:'a[]) n =  // bubble sort, returns number of swaps
    let mutable swapTotal = 0
    
    let mutable i = 0
    while i <> n do
        let mutable swapCount = 0
        
        for j = 0 to n - 2 do
            if a.[j] > a.[j + 1] then
                let tmp = a.[j]
                a.[j] <- a.[j + 1]
                a.[j + 1] <- tmp
                swapCount <- swapCount + 1
        
        swapTotal <- swapTotal + swapCount
        i <- (if swapCount = 0 then n else i + 1)
    
    swapTotal

let n, a =
    let getln = System.Console.ReadLine
    getln () |> int, getln () |> (fun s -> s.Split ' ') |> Array.map int

if Array.length a <> n then failwith "input record not of specified length"

sort a n    |> printfn "Array is sorted in %d swaps."
a.[0]       |> printfn "First Element: %d"
a.[n - 1]   |> printfn "Last Element: %d"
