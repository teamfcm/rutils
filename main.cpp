#include <iostream>
#include <iomanip>
#include "IniManager.hpp"

int main() {
    try {
        rutils::IniFile file("../test.ini");
        rutils::IniFile file2("../test.ini");

        file["test"]["test"] = 4;
        std::cout << "Must be 4 : "  << file["test"]["test"] << std::endl;

        file["test"]["test"] = true;
        std::cout << "Must be true : " << file["test"]["test"] << std::endl;

        file["test"]["test"] = "This is a string";
        std::cout << "Must be This is a string : " << file["test"]["test"] << std::endl;

    } catch (rutils::FileNotFound &e) {
        std::cerr << "An error occured : " << e.what() << std::endl;
        return (1);
    } catch (rutils::InvalidTypeFile &e) {
        std::cerr << "An error occured : " << e.what() << std::endl;
        return (1);
    } catch (rutils::SyntaxError &e) {
        std::cerr << "Syntax error : " << e.what() << std::endl;
        return (1);
    }
    return 0;
}