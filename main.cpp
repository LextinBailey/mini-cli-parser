#include <iostream>
#include "App.hpp"

int main(int argc, char** argv) {
    App app;

    app.add_option("--name", "-n", true, "User name");
    app.add_option("--verbose", "-v", false, "Verbose mode");
    app.add_option("--help", "-h", false, "Show this help menu");

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if(arg == "--help") {
            app.print_help();
            return 0;
        }
    }

    try {
        app.parse(argc, argv);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
        return 1;
    }

    if (app.get_option("--name").is_set) {
        std::cout << "Name: " << app.get_option("--name").value << '\n';
    }

    if (app.get_option("--verbose").is_set) {
        std::cout << "Verbose ON\n";
    }
}