#include <iostream>
#include "App.hpp"

int main(int argc, char** argv) {
    App app;

    app.add_option("--verbose", false, "Verbose mode");

    app.parse(argc, argv);

    if (app.get_option("--verbose").is_set) {
        std::cout << "Verbose is ON\n";
    }
}