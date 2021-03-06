// sorting.fs - like http://fsharpforfunandprofit.com/posts/fvsc-quicksort/

let rec sort list =
    match list with
    | head::tail ->
        let lower = tail |> List.filter (fun x -> x < head) |> sort
        let upper = tail |> List.filter (fun x -> x >= head) |> sort
        List.concat [lower; [head]; upper]
    | [] -> []

[<EntryPoint>] // unit test
let main argv =
    let sortout list = list |> sort |> printfn "%A"

    [1;5;23;18;9;1;3] |> sortout
    [2.3;8.5;1.6;4.4;6.8;0.9] |> sortout
    ["foo";"bar";"baz";"foobar";"quux"] |> sortout
    [10I..20I] |> List.map (fun i -> -i) |> sortout
    [] |> sortout

    0
