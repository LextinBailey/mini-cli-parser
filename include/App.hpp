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

    void parse(int argc, char** argv) {
        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];

            auto it = options.find(arg);
            if(it != options.end()) {
                Option& opt = it->second;
                opt.is_set = true;

                if(opt.expects_value) {
                    if(i + 1 >= argc) continue; 

                    std::string next = argv[i + 1];

                    if(next[0] == '-') continue; 

                    opt.value = next;
                    i++;
                }
            }
        }
    }

    Option& get_option(const std::string& name) {
        return options.at(name);
    }
};