# Mini CLI Parser

A header-only C++ CLI parsing library focused on clarity and design.

A lightweight C++ library for building command-line interfaces with support for short/long flags, combined options, required arguments, and help generation.

## 📝 Overview

Mini CLI Parser is a custom-built command-line parsing library inspired by modern tools like CLI11. It provides a structured way to define, parse, and access command-line arguments in C++.

This project was built to explore how CLI parsers work internally while keeping a clean and usable interface.

## ⚡️ Quick Example

```cpp
#include <iostream>
#include "mini_cli/App.hpp"

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
```

```bash
$ ./example_app --name Dave -v
Verbose ON
Name: Dave
```

## 🔥 Features

### 🛠️ Core Features

- [x] Register CLI options
- [x] Parse raw `argv` input
- [x] Support for short flags (e.g., `-n`)
- [x] Support for combined short flags (e.g., `-vn`)
- [x] Required option enforcement
- [x] Store and retrieve parsed values

### 👨‍💻 Developer Experience

- [x] Built-in help menu
- [x] Error handling for invalid input
- [x] Usage examples

## 💡 What This Demonstrates

This project demonstrates:
- Strong understanding of C++ fundamentals
- Clean separation of concerns between parsing logic and data representation
- Ability to design and structure a reusable component
- Translating real-world library design into a custom implementation

## ⚙️ Build and Usage

### Requirements

C++17 or later

### Build with CMake

```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

### Usage

```bash
$ ./example_app --name Dave -v
Name: Dave
Verbose ON
```

## 📦 Using as a Library

Mini CLI Parser is header-only. Simply include:

```cpp
#include "mini_cli/App.hpp"
```

No linking required.

## 🧠 Design Highlights

- Clear separation between parsing logic (`App`) and data representation (`Option`)
- Converts raw `argv` input into a structured, queryable format through a clear parsing flow.
- Designed to support future features like subcommands and advanced validation.

## ⚙️ How It Works Internally

⚠️ This section is optional and provides a deeper look into the internal design.

The parser is built around two core components: `App` and `Option`.

### 1. Option Registration

All CLI options are registered upfront with `add_option(...)`.

Each option is stored as an `Option` object containing:
- Long name (`--name`)
- Short name (`-n`)
- Whether it's expecting a value
- Description ("User name")
- Required flag
- Runtime state (`is_set`, `value`)

Internally, options are stored in an `std::unordered_map<std::string, Option>`, keyed by the long name for fast lookup.

### 2. Parsing Flow

The `parse(argc, argv)` function processes command-line input sequentially:

1. Iterate through `argv` starting at index 1
2. For each argument:
    - Check if argument is a combination of short flags (e.g., `-vn`)
    - If so, handle each flag separately
    - Call `resolve_option(arg)` helper function
    - Try to match it against a registered long option
    - If not found, check against all short options
3. If no match is found:
    - Throw an error for unknown option
4. If matched:
    - Return the option
    - Mark the option as `is_set = true`
    - If the option expects a value:
        - Call `handle_value(opt, i, argc, argv, arg)` helper function
        - Read the next argument
        - Validate it's not another flag
        - Store it in `option.value`
        - Advance the iterator

This ensures a predictable left-to-right parsing process.

### 3. Short Flag Resolution

Short flags (e.g., `-n`) are resolved using a secondary `std::unordered_map` that maps short names directly to their corresponding `Option` objects.

The resolved option is treated as the canonical reference for storing and accessing parsed data.

Earlier implementations used a linear search across registered options. This was optimized using a hash map to improve lookup performance.

### 4. Combined Flag Resolution

Combined flags (e.g., `-vn`) are resolved by iterating through each flag.

If a flag expects a value, validation ensures the flag is the last flag in the group.

### 5. Required Option Validation

After parsing, `validate_required()` ensures all required options were provided.

- Iterates through all registered options
- Throws an error if any required option was not set

This separates parsing logic from validation.

### 6. Data Access

Parsed data is accessed through:

```cpp
app.get_option("--name")
```

Each `Option` object exposes:
- `is_set`: whether the flag was provided
- `value`: the associated argument (if required)

### 7. Error Handling

Errors are handled using exceptions (`std::runtime_error`) for cases:
- Unknown options
- Missing values
- Invalid values
- Missing required arguments
- Option requiring value not the last flag in the group

This allows the calling code to manage failures cleanly.

### 8. Help Menu

The help menu is generated dynamically from registered options.

- Iterates through all options
- Prints name (long and short), descriptions, and required flags
- Uses simple spacing for readability

Will print after an exception is caught if `--help` has been set

## 📁 Project Structure

```
mini-cli-parser/
├── CMakeLists.txt
├── include/
│   └── mini_cli/
│       ├── App.hpp
│       └── Option.hpp
├── examples/
│   └── main.cpp
├── src/
├── progress-log.md
└── README.md
```

## 🧩 Design Summary

- Single Responsibility
    - `Option` represents data, `App` handles parsing logic

- Efficient Single-Pass Parsing
    - Parses input in one pass with predictable behavior and optimized flag resolution using constant-time lookups

- Extensible Structure
    - Planned features can be added without major refactoring

## 📈 Development Notes

Progress and development insights are tracked in `progress-log.md`.

## 🔮 Inspiration

This project is inspired by the design of the CLI11 library: https://github.com/CLIUtils/CLI11