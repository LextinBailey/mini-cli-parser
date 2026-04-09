#pragma once

#include <string>
#include <unordered_map>
#include "Option.hpp"

class App {
private:
    std::unordered_map<std::string, Option> options;

public:
    void add_option(const std::string& name, bool expects_value, const std::string& description) {
        Option opt;

        opt.name = name;
        opt.expects_value = expects_value;
        opt.description = description;

        options.emplace(name, opt);
    }

    void parse(int argc, char** argv) {}

    Option& get_option(const std::string& name) {
        return options.at(name);
    }
};