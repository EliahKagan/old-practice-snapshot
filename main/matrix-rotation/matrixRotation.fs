open System

let readRow = Console.ReadLine >> (fun s -> s.Split ' ') >> Array.map int

let readMatrix m n =
    let rows = Array.replicate m () |> Array.map readRow
    if not (Array.forall (Array.length >> (=) n) rows) then failwith "bad row"
    if Console.ReadLine () <> null then failwith "final row not end of input"
    Array2D.init m n (fun i j -> rows.[i].[j])

let shell imin jmin imax jmax (matrix:'a[,]) =
    Array.concat [matrix.[imin .. imax - 1, jmin];
                  matrix.[imax, jmin .. jmax  - 1];
                  Array.rev matrix.[imin + 1 .. imax, jmax];
                  Array.rev matrix.[imin, jmin + 1 .. jmax]]

let cycle r (s:'a[]) =
    let n = Array.length s
    let i = n - (r % n)
    Array.concat [s.[i ..]; s.[.. i - 1]];

let pairs imin jmin imax jmax (s:'a[]) =
    let vertical, horizontal = imax - imin, jmax - jmin
    
    let down = vertical - 1
    let right = down + horizontal
    let up = right + vertical
    let left = up + horizontal

    if (left + 1) <> Array.length s then failwith "shell not of specified size"

    Seq.concat [Seq.mapi (fun i x -> (imin + i, jmin), x) s.[0 .. down];
                Seq.mapi (fun j x -> (imax, jmin + j), x) s.[down + 1 .. right];
                Seq.mapi (fun i x -> (imax - i, jmax), x) s.[right + 1 .. up];
                Seq.mapi (fun j x -> (imin, jmax - j), x) s.[up + 1 .. left]]

let cycleAll r depth m n (matrix:'a[,]) =
    let peel d =
        let dm, dn = m - 1 - d, n - 1 - d
        shell d d dm dn matrix |> cycle r |> pairs d d dm dn

    let xs = {0 .. depth - 1} |> Seq.collect peel |> Map
    Array2D.init m n (fun i j -> xs.[i, j])

let print m n (matrix:int[,]) =
    for i = 0 to m - 1 do
        {0 .. n - 1} |> Seq.map (fun j -> matrix.[i, j] |> string)
                     |> String.concat " " |> Console.WriteLine

[<EntryPoint>]
let main argv =
    let m, n, r = let mnr = readRow () in mnr.[0], mnr.[1], mnr.[2]
    if not (m > 1 && n > 1 && r > 0) then failwith "input(s) out of range"
    
    let depth =
        let small = min m n
        if small % 2 = 0 then small / 2 else failwith "need min(M, N) even"

    readMatrix m n |> cycleAll r depth m n |> print m n
    0
