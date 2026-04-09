#pragma once

#include <string>

class Option {
public:
    std::string name;
    std::string short_name;
    bool expects_value;
    std::string description;

    bool required = false;

    std::string value;
    bool is_set = false;
};