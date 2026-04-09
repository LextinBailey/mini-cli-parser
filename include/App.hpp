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
    void add_option(const std::string& name, const std::string& short_name ,bool expects_value, const std::string& description, bool required = false) {
        Option opt;

        opt.name = name;
        opt.short_name = short_name;
        opt.expects_value = expects_value;
        opt.description = description;
        opt.required = required;

        options.emplace(name, opt);
    }

    void print_help() const {
        std::cout << "Options:\n";

        for (const auto& pair : options) {
            const Option& opt = pair.second;

            std::cout << "  " << opt.name << ", " << opt.short_name;

            if (opt.name.length() < 14) {
                std::cout << std::string(14 - opt.name.length(), ' ');
            }
                     
            std::cout << opt.description;

            if (opt.required) {
                std::cout << " (required)";
            }

            std::cout << '\n';
        }
    }

    void parse(int argc, char** argv) {
        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];

            auto it = options.find(arg);

            if (it == options.end()) {
                for (auto& pair : options) {
                    if (pair.second.short_name == arg) {
                        it = options.find(pair.first);
                        break;
                    }
                }

                if (it == options.end()) {
                    throw std::runtime_error("Unknown option: " + arg);
                }
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

    void validate_required() const {
        for (const auto& pair : options) {
            const Option& opt = pair.second;

            if (opt.required && !opt.is_set) {
                throw std::runtime_error("Missing required option: " + opt.name);
            }
        }
    }

    Option& get_option(const std::string& name) {
        return options.at(name);
    }
};