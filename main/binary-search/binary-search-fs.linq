<Query Kind="FSharpProgram" />

let binarySearch (words: 'a array) key =
    let rec loop low high =
        if high < low then
            -1 // not found
        else
            let mid = (low + high) / 2 // the '/' operation does integer division
            
            if words.[mid] < key then
                loop (mid + 1) high // check right of mid
            elif words.[mid] > key then
                loop low (mid - 1)  // check left of mid
            else
                mid
    
    loop 0 (Array.length words)

let getWords () =
   System.Console.ReadLine().Split()

let showBinarySearch (words: string array) key =
    printfn "%s: %d" key (binarySearch words key)

printfn "Please enter some words to populate the dictionary."
let words = getWords () |> Array.sort // binary search requires sorted array

printfn ""
printfn "Sorted, that list looks like:"
String.concat " " words |> printfn "%s"

printfn ""
printfn "What words do you want to find in the sorted list?"
let keys = getWords ()

printfn ""
keys |> Array.iter (showBinarySearch words)
