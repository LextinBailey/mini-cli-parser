#pragma once

#include <string>

class Option {
public:
    std::string name;
    bool expects_value;
    std::string description;

    std::string value;
    bool is_set = false;
};