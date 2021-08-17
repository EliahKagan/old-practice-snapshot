#define CBEGIN_CEND_NOT_AVAILABLE

#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

namespace {
#ifdef CBEGIN_CEND_NOT_AVAILABLE // horrible hacky kludge for HackerRank
#define cbegin(items) ((items).cbegin())
#define cend(items) ((items).cend())
#else
    using std::cbegin;
    using std::cend;
#endif // ! CBEGIN_CEND_NOT_AVAILABLE

    class MalformedTagException : public std::invalid_argument {
        using std::invalid_argument::invalid_argument;
    };

    template<typename T>
    T dequeue(std::queue<T>& que)
    {
        const T x {std::move(que.front())};
        que.pop();
        return x;
    }

    std::string join(const char sep, const std::string& lhs,
                                     const std::string& rhs)
    {
        std::ostringstream out;
        out << lhs << sep << rhs;
        return out.str();
    }

    std::queue<std::string> extract_tags(const std::string& s)
    {
        std::queue<std::string> tags;

        std::regex r {R"(<[^>"]*(?:"[^"]*"[^>"]*)*>)"};
        
        const auto q = std::sregex_iterator{};
        for (auto p = std::sregex_iterator{cbegin(s), cend(s), r}; p != q; ++p)
            tags.push(p->str());

        return tags;
    }

    std::string extract_tag_name(const std::string& tag)
    {
        std::regex r {R"([^<>"=\s]+(?=[\s>])(?!\s*=))"};

        const auto p = std::sregex_iterator{cbegin(tag), cend(tag), r};
        if (p == std::sregex_iterator{})
            throw MalformedTagException{"tag encountered without name"};

        return p->str();
    }

    void extract_tag_attributes(
            std::unordered_map<std::string, std::string>& attrs,
            const std::string& tag, const std::string& path)
    {
        std::regex r {R"_(([^<>"=\s]+)\s*=\s*"([^"]+)")_"};
        
        const auto q = std::sregex_iterator{};
        for (auto p = std::sregex_iterator{cbegin(tag), cend(tag), r}; p != q;
                                                                       ++p) {
            attrs.insert(std::make_pair(join('~', path, p->str(1u)),
                                        p->str(2u)));
        }
    }

    void extract_multiple_tags_attributes(
            std::unordered_map<std::string, std::string>& attrs,
            std::queue<std::string>& tags, const std::string& path)
    {
        while (!tags.empty()) {
            const auto tag = dequeue(tags), name = extract_tag_name(tag);
            if (name[0] == '/') break; // got end tag (assume proper nesting)

            const auto newpath = path.empty() ? name : join('.', path, name);
            extract_tag_attributes(attrs, tag, newpath);
            extract_multiple_tags_attributes(attrs, tags, newpath);
        }
    }

    std::unordered_map<std::string, std::string>
    extract_all_tag_attributes(const std::string& s)
    {
        auto tags = extract_tags(s);

        std::unordered_map<std::string, std::string> attrs;
        extract_multiple_tags_attributes(attrs, tags, std::string{});

        return attrs;
    }

    std::string read_line()
    {
        std::string s;
        std::getline(std::cin, s);
        return s;
    }

    std::string read_multiple_lines(int n)
    {
        std::ostringstream out;
        while (n-- > 0) out << read_line();
        return out.str();
    }

    std::vector<int> read_line_as_record()
    {
        std::vector<int> a;

        std::istringstream in { read_line()};
        int x {};
        while (in >> x) a.push_back(x);

        return a;
    }

    std::string read_word()
    {
        std::string s;
        std::cin >> s;
        return s;
    }

    std::unordered_map<std::string, std::string>
    read_all_tag_attributes(const int markup_length_in_lines)
    {
        const auto s = read_multiple_lines(markup_length_in_lines);
        return extract_all_tag_attributes(s);
    }

    void run_queries(const std::unordered_map<std::string, std::string>& attrs,
                     int queries_left)
    {
        for (const auto q = cend(attrs); queries_left > 0; --queries_left) {
            const auto p = attrs.find(read_word());

            if (p == q) std::cout << "Not Found!\n";
            else std::cout << p->second << '\n';
        }
    }
}

int main()
{
    const auto input_size = read_line_as_record();
    const auto attrs = read_all_tag_attributes(input_size.at(0u));
    run_queries(attrs, input_size.at(1u));
}
