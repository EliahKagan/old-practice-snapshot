<Query Kind="FSharpProgram" />

open System

let pascal height =
    let nextRow prev =
        [|  yield 1
        
            for i = 0 to Array.length prev - 2 do
                yield prev.[i] + prev.[i + 1]
                
            yield 1     |]
            
    let rec pascalTo n prev =
        [   yield prev
            if Array.length prev < n then
                yield! nextRow prev |> pascalTo n   ]
    
    pascalTo height [|1|]

//[<EntryPoint>]
let main argv =
    let getOne () = Console.ReadLine () |> int
    let putMany (row:int[]) = String.Join (" ", row) |> printfn "%s"
    
    getOne () |> pascal |> List.iter putMany

main ()