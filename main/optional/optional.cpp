// Example usage of std::optional. This program incorporates information
// obtained from http://harrypotter.wikia.com.

#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

namespace {
    class WizardConstructionError : public std::logic_error {
        using std::logic_error::logic_error;
    };

    class Wizard {
    public:
        const std::string& surname() const noexcept { return surname_; }
        const std::string& given_name() const noexcept { return given_name_; }
        const std::string& animagus() const noexcept { return animagus_; }
        const std::string& patronus() const noexcept { return patronus_; }
        const std::string& birthplace() const noexcept { return birthplace_; }
        const std::string& house() const noexcept { return house_; }
        const std::string& title() const noexcept { return title_; }
        // Fascist bug reports requesting a blood status field will be rejected.

    private:
        friend class WizardFactory;

        Wizard() = default;

        std::string surname_;
        std::string given_name_;
        std::string animagus_;
        std::string patronus_;
        std::string birthplace_;
        std::string house_;
        std::string title_; // TODO: support multiple titles
    };

    class WizardFactory {
    public:
        // Set the properties of the wizard that will be made.
        WizardFactory& surname(std::string val) { return set(surname_, val); }
        WizardFactory& given_name(std::string val) { return set(given_name_, val); }
        WizardFactory& animagus(std::string val) { return set(animagus_, val); }
        WizardFactory& patronus(std::string val) { return set(patronus_, val); }
        WizardFactory& birthplace(std::string val) { return set(birthplace_, val); }
        WizardFactory& house(std::string val) { return set(house_, val); }
        WizardFactory& title(std::string val) { return set(title_, val); }

        // Make the wizard.
        Wizard operator()();

    private:
        WizardFactory& set(std::optional<std::string>& target, std::string& val);
        std::string get(std::optional<std::string>& source);

        std::optional<std::string> surname_;
        std::optional<std::string> given_name_;
        std::optional<std::string> animagus_;
        std::optional<std::string> patronus_;
        std::optional<std::string> birthplace_;
        std::optional<std::string> house_;
        std::optional<std::string> title_;
    };

    std::ostream& operator<<(std::ostream& out, const Wizard& wizard)
    {
        return out << "Surname:    " << wizard.surname() << '\n'
                   << "Given name: " << wizard.given_name() << '\n'
                   << "Animagus:   " << wizard.animagus() << '\n'
                   << "Patronus:   " << wizard.patronus() << '\n'
                   << "Birthplace: " << wizard.birthplace() << '\n'
                   << "House:      " << wizard.house() << '\n'
                   << "Title:      " << wizard.title() << '\n';
    }

    Wizard WizardFactory::operator()()
    {
        Wizard wizard;
        
        try {
            wizard.surname_ = get(surname_);
            wizard.given_name_ = get(given_name_);
            wizard.animagus_ = get(animagus_);
            wizard.patronus_ = get(patronus_);
            wizard.birthplace_ = get(birthplace_);
            wizard.house_ = get(house_);
            wizard.title_ = get(title_);
        }
        catch (const std::bad_optional_access&) {
            throw WizardConstructionError{
                    "too little information to make a wizard"};
        }

        return wizard;
    }

    inline WizardFactory&
    WizardFactory::set(std::optional<std::string>& target, std::string& val)
    {
        if (target.has_value())
            throw WizardConstructionError{"attempt to set a field twice"};

        target = std::move(val);

        return *this;
    }

    inline std::string WizardFactory::get(std::optional<std::string>& source)
    {
        return std::move(source.value());
    }
}

int main()
{
    // We know everything we need to know about McGonagall. This doesn't throw.
    const auto mcgonagall = WizardFactory{}.surname("McGonagall")
                                           .given_name("Minerva")
                                           .animagus("Tabby Cat")
                                           .patronus("Cat")
                                           .birthplace("Caithness, Scotland")
                                           .house("Gryffindor")
                                           .title("Professor")();
    std::cout << mcgonagall << '\n';

    try {
        // We don't know very much about Hagrid's dad...
        const auto mr_hagrid = WizardFactory{}.surname("Hagrid")(); // throws
        std::cout << mr_hagrid << "\n\n"; // won't run
    }
    catch (const WizardConstructionError& e) {
        std::cout << "We got an error for Hagrid's dad:        "
                  << e.what() << "\n\n";
    }

    try {
        // If we specify the same field twice, even with different values, the
        // exception is thrown for that (and not, for example, that Hermione has
        // no known animagus).
        const auto hermione = WizardFactory{}.surname("Granger")
                                             .given_name("Hermione")
                                             .house("Gryffindor")
                                             .title("Prefect")
                                             .patronus("Otter")
                                             .title("Leader of S.P.E.W")
                                             .birthplace("somewhere in England")();
        std::cout << hermione << "\n\n"; // won't run
    }
    catch (const WizardConstructionError& e) {
        std::cout << "We got an error for Hermione Granger:    "
                  << e.what() << "\n\n";
    }
}
