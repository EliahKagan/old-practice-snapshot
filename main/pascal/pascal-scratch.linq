<Query Kind="FSharpProgram" />

let nextRow prev =
    [|  yield 1
    
        for i = 0 to Array.length prev - 2 do
            yield prev.[i] + prev.[i + 1]
            
        yield 1     |]
        
let rec pascalTo n prev =
    [   yield prev
        if Array.length prev < n then
            yield! nextRow prev |> pascalTo n   ]

nextRow [|1|] |> Dump
nextRow [|1;1|] |> Dump
nextRow [|1;2;1|] |> Dump
nextRow [|1;3;3;1|] |> Dump

pascalTo 1 [|1|] |> Dump
pascalTo 2 [|1|] |> Dump
pascalTo 3 [|1|] |> Dump
pascalTo 4 [|1|] |> Dump