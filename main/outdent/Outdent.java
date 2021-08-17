// Outdent.java - The command "java Outdent m n infile outfile" copies infile
//                to outfile, but when a line is indented least m spaces,
//                unindents it by n spaces.

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

final class Util {
    public static void die(final String message)
    {
        System.err.format("error: %s%n", message);
        System.exit(1);
    }
    
    public static void die(final String format, final Object... args)
    {
        die(String.format(format, args));
    }
    
    private Util() { } // the Util class should not be instantiated
}

final class Errand {
    public final String inpath, outpath;
    public final int indent, outdent;
    
    public Errand(final String[] args)
    {
        if (args.length != NUM_ARGS) {
            Util.die("too %s arguments",
                     args.length < NUM_ARGS ? "few" : "many");
        }
        
        try {
            indent = Integer.parseInt(args[0]);
            outdent = Integer.parseInt(args[1]);
        }
        catch (final NumberFormatException e) {
            Util.die("indent and outdent must be numbers (integers)");
            throw new AssertionError();
        }
        
        if (indent <= 0) Util.die("indent must be positive");
        if (outdent >= indent) Util.die("outdent must be less than indent");
        
        inpath = args[2];
        outpath = args[3];
    }
    
    private static final int NUM_ARGS = 4;
}

final class Outdent {
    private static String getIndentText(int indent)
    {
        final StringBuilder sb = new StringBuilder();
        while (indent-- != 0) sb.append(' ');
        return sb.toString();
    }
    
    private static void outdent(final int indent, final int outdent,
            final BufferedReader in, final BufferedWriter out)
            throws IOException
    {
        final String prefix = getIndentText(indent);
        
        for (String line; (line = in.readLine()) != null; ) {
            if (line.startsWith(prefix)) line = line.substring(outdent);
            out.write(line);
            out.newLine();
        }
    }
    
    public static void main(final String[] args)
    {
        final Errand errand = new Errand(args);
        
        try (final BufferedReader in =
                    new BufferedReader(new FileReader(errand.inpath));
             final BufferedWriter out =
                    new BufferedWriter(new FileWriter(errand.outpath))) {
            outdent(errand.indent, errand.outdent, in, out);
        }
        catch (final IOException e) {
            Util.die(e.getMessage());
        }
    }
    
    private Outdent() { } // the Outdent class should not be instantiated
}
