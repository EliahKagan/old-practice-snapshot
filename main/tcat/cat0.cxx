// cat0.cxx - simple program implementing a subset of cat's functionality

#include <algorithm>
#include <codecvt>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <locale>
#include <string>
#include <vector>

namespace {
    const char* progname; // set in main
    int status = EXIT_SUCCESS;

    std::ostream& err(bool error = true)
    {
        if (error) status = EXIT_FAILURE;
        return std::cerr << progname << (error ? ": error: " : ": warning: ");
    }

    inline std::ostream& warn()
    {
        return err(false);
    }

    std::wstring widen(const std::string& s) // FIXME: use current locale!!
    {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif
        static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
#ifdef __clang__
#pragma clang diagnostic pop
#endif
        return conv.from_bytes(s);
    }

    [[noreturn]] void help()
    {
        std::wcout << 
            L"Usage:  cat0 [{-v | --verbose | - | file}...] [-- [file...]]\n\n"
            L"        file          :  name of file to copy to standard output\n"
            L"        -             :  copy standard input to standard output\n"
            L"        --            :  interpret all subsequent arguments as filenames\n"
            L"        -v, --verbose :  output filename headings before file contents\n"
            L"        -q, --quiet   :  don't output filename headings (default)\n";

        std::exit(EXIT_SUCCESS);
    }

    void print_header(const std::string* pathp)
    {
        static bool needs_leading_newline = false;
        if (needs_leading_newline) std::wcout << L'\n';
        else needs_leading_newline = true;

        if (pathp == nullptr)
            std::wcout << L"====> (standard input) <====\n";
        else
            std::wcout << L"==> " << widen(*pathp) << " <==\n";
    }

    bool cat(std::wistream& in) // true on success
    {   
        for (std::wstring line; std::getline(in, line); )
            std::wcout << line << L'\n';

        return !in.bad() && in.eof();
    }

    void cat_stdin(bool verbose)
    {
        if (std::wcin.good()) {
            if (verbose) print_header(nullptr);

            if (cat(std::wcin)) std::wcin.clear(); // clear eof for next read
            else err() << "failure reading standard input\n";
        }
        else warn() << "not trying standard input again\n";
    }

    void cat_file(const std::string& path, bool verbose)
    {
        if (std::wifstream in {path}) {
            if (verbose) print_header(&path);
            if (!cat(in)) err() << "failure reading file \"" << path << "\"\n";
        } else {
            err() << "couldn't open file \"" << path << "\"\n";
        }
    }
}

int main(int argc, char** argv)
{
    progname = argv[0], --argc, ++argv;
    const auto end = argv + argc;

    bool verbose {false};
    std::vector<const char*> paths;
    paths.reserve(static_cast<decltype(paths)::size_type>(argc)); //OK, argc>=0

    // consume paths and options up to the first "--" argument
    for (; argv != end; ++argv) {
        if ((*argv)[0] == '\0') continue; // skip blank filenames
        
        if ((*argv)[0] != '-') {
            paths.push_back(*argv);
            continue;
        }

        const std::string opt {*argv};

        if (opt.length() == 1) paths.push_back(nullptr); // stdin specified
        else if (opt == "--") {
            ++argv;
            break;
        }
        else if (opt == "-v" || opt == "--verbose") verbose = true;
        else if (opt == "-q" || opt == "--quiet") verbose = false;
        else if (opt == "-h" || opt == "--help") help();
        else err() << "unrecognized option \"" << opt << "\"\n";
    }

    if (status != EXIT_SUCCESS) return status; // there were unrecognized opts

    // consume the remaining arguments, if any, as paths (unless blank)
    std::copy_if(argv, end, std::back_inserter(paths),
                 [](const char* a) { return a[0] != '\0'; });

    // we'll handle output failure immediately (cat is often redirected/piped!)
    std::wcout.exceptions(std::ios_base::badbit
        | std::ios_base::failbit | std::ios_base::eofbit);

    // proceed to copy from inputs to standard output
    try {
        if (paths.empty()) cat_stdin(verbose); // default input is stdin
        else {
            for (auto path : paths)
                path == nullptr ? cat_stdin(verbose) : cat_file(path, verbose);
        }

        std::wcout << std::flush;
    }
    catch (const std::ios_base::failure&) {
        err() << "failure writing standard output\n";
    }
    
    return status;
}
