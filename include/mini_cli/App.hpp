#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "Option.hpp"

class App {
private:
    std::unordered_map<std::string, Option> options;
    std::unordered_map<std::string, Option*> short_options;

public:
    void add_option(const std::string& name, const std::string& short_name ,bool expects_value, const std::string& description, bool required = false) {
        Option opt;

        opt.name = name;
        opt.short_name = short_name;
        opt.expects_value = expects_value;
        opt.description = description;
        opt.required = required;

        auto [it, inserted] = options.emplace(name, opt);

        if (!short_name.empty()) {
            short_options[short_name] = &it->second;
        }
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

    Option& resolve_option(const std::string& arg) {
        auto it = options.find(arg);

        if (it != options.end()) {
            return it->second;
        }

        auto sit = short_options.find(arg);
        if (sit != short_options.end()) {
            return *sit->second;
        }

        throw std::runtime_error("Unknown option: " + arg);
    }

    void handle_value(Option& opt, int& i, int argc, char** argv, const std::string& arg) {
        if (!opt.expects_value) return;

        if (i + 1 >= argc) {
            throw std::runtime_error("Missing value for option: " + arg);
        }

        std::string next = argv[i + 1];

        if(next[0] == '-') {
            throw std::runtime_error("Invalid value for option: " + arg);
        }

        opt.value = next;
        i++;
    }

    void parse(int argc, char** argv) {

        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];

            if (arg.length() > 2 && arg[0] == '-' && arg[1] != '-') {
                for(size_t j = 1; j < arg.length(); j++) {
                    std::string short_flag = "-" + std::string(1, arg[j]);

                    Option& opt = resolve_option(short_flag);
                    opt.is_set = true;

                    if(opt.expects_value) {
                        if (j != arg.length() - 1) {
                            throw std::runtime_error("Option requiring value must be last in group: " + short_flag);
                        }

                        handle_value(opt, i, argc, argv, short_flag);
                    }
                }

                continue;
            }
 
            Option& opt = resolve_option(arg);
            opt.is_set = true;

            handle_value(opt, i, argc, argv, arg);
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