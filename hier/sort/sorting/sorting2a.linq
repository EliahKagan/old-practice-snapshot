<Query Kind="FSharpProgram" />

let rec sort = function
    | x::xs ->
        let high,low = List.partition ((<) x) xs
        List.concat [sort low; [x]; sort high]
    | [] -> []

let sortout list = list |> sort |> printfn "%A"

[1;5;23;18;9;1;3] |> sortout
[2.3;8.5;1.6;4.4;6.8;0.9] |> sortout
["foo";"bar";"baz";"foobar";"quux"] |> sortout
[10I..20I] |> List.map (fun i -> -i) |> sortout
[] |> sortout