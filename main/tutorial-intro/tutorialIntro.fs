open System

let notFound = -1

let rec bsearch (array:_[]) key startIndex stopIndex =
    let i = startIndex + (stopIndex - startIndex) / 2
    
    if stopIndex < startIndex then notFound
    elif key < array.[i] then bsearch array key startIndex (i - 1)
    elif key > array.[i] then bsearch array key (i + 1) stopIndex
    else i

let split (str:string) = str.Split ' '
let getOne () = Console.ReadLine () |> int
let getMany () = Console.ReadLine () |> split |> Array.map int

let v = getOne ()
let n = getOne () |> max 0
let a = getMany ()

Array.length a - 1 |> min n |> bsearch a v 0 |> printfn "%d"
