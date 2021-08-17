open System
open System.Text

[<Literal>]
let BufferSize = 6000000

[<Literal>]
let Append = 1

[<Literal>]
let Erase = 2

[<Literal>]
let Print = 3

[<Literal>]
let Undo = 4

let append (str : string) (buf : StringBuilder) =
    buf.Append str

let erase len (buf : StringBuilder) =
    buf.Length <- buf.Length - len
    buf

let editAppend str (buf : StringBuilder, undos) =
    let undo = String.length str |> erase
    append str buf, undo::undos

let editErase len (buf : StringBuilder, undos) =
    let undo = (string buf).[(buf.Length - len)..] |> append
    erase len buf, undo::undos

let editPrint i (buf : StringBuilder, undos) =
    buf.[i - 1] |> Console.WriteLine
    buf, undos

let editUndo (buf : StringBuilder, undos) =
    match undos with
    | undo::undos'  -> undo buf, undos'
    | []            -> failwith "no last operation to undo"

let resolveQuery (query : string array) =
    match int query.[0] with
    | Append    -> editAppend query.[1]
    | Erase     -> editErase (int query.[1])
    | Print     -> editPrint (int query.[1])
    | Undo      -> editUndo
    | _         -> failwith "unrecognized query kind"

let run =
    let edit acc query = resolveQuery query acc
    let seed = StringBuilder (BufferSize, BufferSize), []
    Seq.fold edit seed

let rec lines () =
    seq {
        match Console.ReadLine () with
        | null -> ()
        | line ->
            yield   line
            yield!  lines ()
    }

let queries =
    let rec lines () =
        seq {
            match Console.ReadLine () with
            | null -> ()
            | line ->
                yield   line
                yield!  lines ()
        }
    
    lines ()
    |> Seq.skip 1 // ignore Q value; apparently it is unreliable
    |> Seq.map (fun s -> s.Split ' ')

queries |> run |> ignore
