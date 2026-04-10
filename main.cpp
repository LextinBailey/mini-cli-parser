#include <iostream>
#include "App.hpp"

int main(int argc, char** argv) {
    App app;

    app.add_option("--name", "-n", true, "User name", true);
    app.add_option("--verbose", "-v", false, "Verbose mode");
    app.add_option("--help", "-h", false, "Show this help menu");

    try {
        app.parse(argc, argv);
        app.validate_required();
    } catch (const std::exception& e) {
        if (app.get_option("--help").is_set) {
            app.print_help();
            return 0;
        }

        std::cout << "Error: " << e.what() << '\n';
        return 1;
    }

    if (app.get_option("--name").is_set) {
        std::cout << "Name: " << app.get_option("--name").value << '\n';
    }

    if (app.get_option("--verbose").is_set) {
        std::cout << "Verbose ON\n";
    }

    if (app.get_option("--help").is_set) {
        app.print_help();
        return 0;
    }
}