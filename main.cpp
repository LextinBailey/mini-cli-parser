#include <iostream>
#include "App.hpp"

int main(int argc, char** argv) {
    App app;

    app.add_option("--name", true, "User name");

    app.parse(argc, argv);

    if (app.get_option("--name").is_set) {
        std::cout << "Name: " << app.get_option("--name").value << '\n';
    }
}