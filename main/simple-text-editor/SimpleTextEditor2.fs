type buffer = System.Text.StringBuilder
type editor = buffer * (buffer -> buffer) list

module Buffer =
    [<Literal>]
    let private size = 6000000
    
    let inline create () = buffer (size, size)
    
    let append (str : string) (buf : buffer) =
        buf.Append str
    
    let erase len (buf : buffer) =
        buf.Length <- buf.Length - len
        buf

module Editor =
    let inline create () : editor = Buffer.create (), []

    let append str (buf : buffer, undos) =
        let undo = String.length str |> Buffer.erase
        Buffer.append str buf, undo::undos
    
    let erase len (buf : buffer, undos) =
        let undo = (string buf).[(buf.Length - len)..] |> Buffer.append
        Buffer.erase len buf, undo::undos
    
    let print i (buf : buffer, undos) =
        buf.[i - 1] |> stdout.WriteLine
        buf, undos
    
    let undo (buf : buffer, undos) =
        match undos with
        | undo::undos'  -> undo buf, undos'
        | []            -> failwith "no last operation to undo"

let queries =
    let interpret (tok : string array) =
        match int tok.[0] with
        | 1 -> Editor.append tok.[1]
        | 2 -> Editor.erase (int tok.[1])
        | 3 -> Editor.print (int tok.[1])
        | 4 -> Editor.undo
        | _ -> failwith "unrecognized query kind"
    
    let rec lines () =
        seq {
            match stdin.ReadLine () with
            | null -> ()
            | line ->
                yield   line
                yield!  lines ()
        }
    
    lines ()
    |> Seq.skip 1 // ignore Q value; apparently it is unreliable
    |> Seq.map (fun s -> s.Split ' ' |> interpret)

queries |> Seq.fold (|>) (Editor.create ()) |> ignore
