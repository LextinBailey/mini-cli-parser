#pragma once

#include <iostream>
#include <stdexcept>
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

    void parse(int argc, char** argv) {
        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];

            auto it = options.find(arg);

            if (it == options.end()) {
                throw std::runtime_error("Unknown option: " + arg);
            }
 
            Option& opt = it->second;
            opt.is_set = true;

            if(opt.expects_value) {
                if(i + 1 >= argc) {
                    throw std::runtime_error("Missing value for option: " + arg);
                } 

                std::string next = argv[i + 1];

                if(next[0] == '-') {
                    throw std::runtime_error("Invalid value for option: " + arg);
                }

                opt.value = next;
                i++;
            }
        }
    }

    Option& get_option(const std::string& name) {
        return options.at(name);
    }

    void print_help() const {
        std::cout << "Options:\n";

        for (const auto& pair : options) {
            const Option& opt = pair.second;

            std::cout << "  " << opt.name;

            if (opt.name.length() < 14) {
                std::cout << std::string(14 - opt.name.length(), ' ');
            }
                     
            std::cout << opt.description << '\n';
        }
    }
};