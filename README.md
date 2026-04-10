# Mini CLI Parser

A lightweight command-line argument parser written in C++. Focused on clarity, simplicity, and extensibility.

## 📝 Overview

Mini CLI Parser is a custom-built command-line parsing library inspired by modern tools like CLI11. It provides a structured way to define, parse, and access command-line arguments in C++ applications.

This project was built to explore how CLI parsers work internally while keeping a clean and usable interface.

It is designed as both a practical utility and a demonstration of clean C++ design principles.

## 🎯 Purpose

This project demonstrates:
- Strong understanding of C++ fundamentals
- Clean separation of concerns between parsing logic and data representation
- Ability to design and structure a reusable component
- Translating real-world library design into a custom implementation

## 🔥 Features

### ✅ Implemented

- [x] Register CLI options
- [x] Parse raw `argv` input
- [x] Support for short flags (e.g., `-n`)
- [x] Required option enforcement
- [x] Store and retrieve parsed values
- [x] Built-in help menu
- [x] Error handling for invalid input

### 🧱 Planned

- [ ] Combined short flags (e.g., `-abc`)
- [ ] Usage examples
- [ ] Additional validation and type handling

## 🛠️ Example Usage

```cpp
#include <iostream>
#include "App.hpp"

int main(int argc, char** argv) {
    App app;

    app.add_option("--name", "-n", true, "User name", true);
    app.add_option("--verbose", "-v", false, "Verbose mode");

    try {
        app.parse(argc, argv);
        app.validate_required();
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
```

## 🧠 Design Highlights

- Separation of Concerns
    - `App` manages overall parsing, while `Option` encapsulates individual argument behavior.
- Structured Parsing Flow
    - Converts raw `argv` input into a structured, queryable format.
- Extensible Architecture 
    - Designed to support future features like subcommands and advanced validation.

## ⚙️ Build and Usage

### Build

```bash
$ mkdir -p build
$ g++ -Iinclude main.cpp -o build/app
```

### Usage

```bash
$ ./build/app --name Dave -v
Name: Dave
Verbose ON
```

## 📁 Project Structure

```
mini-cli-parser/
|-- include/
|   |-- App.hpp
|   |__ Option.hpp
|-- main.cpp
|-- README.md
|-- progress-log.md
```

## ⚙️ How It Works Internally

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

1. Iterate through `argv` starting at index 1 (Ignoring `./build/app`)
2. For each argument:
    - Try to match it against a registered long option
    - If not found, check against all short options
3. If no match is found:
    - Throw an error for unknown option
4. If matched:
    - Mark the option as `is_set = true`
    - If the option expects a value:
        - Read the next argument
        - Validate it's not another flag
        - Store it in `option.value`
        - Advance the iterator

This ensures a predictable left-to-right parsing process.

### 3. Short Flag Resolution

Short flags (e.g., `-n`) are resolved by iterating through all registered options and matching against `short_name`.

Once found, the corresponding long option is used as the canonical reference.

### 4. Required Option Validation

After parsing, `validate_required()` ensures all required options were provided.

- Iterates through all registered options
- Throws an error if any required option was not set

This separates parsing logic from validation.

### 5. Data Access

Parsed data is accessed through:

```cpp
app.get_option("--name")
```

Each `Option` object exposes:
- `is_set`: whether the flag was provided
- `value`: the associated argument (if required)

### 6. Error Handling

Errors are handled using exceptions (`std::runtime_error`) for cases:
- Unknown options
- Missing values
- Invalid values
- Missing required arguments

This allows the calling code to manage failures cleanly.

### 7. Help Menu

The help menu is generated dynamically from registered options.

- Iterates through all options
- Prints name (long and short), descriptions, and required flags
- Uses simple spacing for readability

Iterates through command-line inpute before parsing to check for `"--help"` or `"-h"` to ensure no errors block the help menu.

## 🧩 Design Summary

- Single Responsibility
    - `Option` represents data, `App` handles parsing logic

- Linear Parsing Strategy
    - Processes input in one pass with predictable behavior

- Extensible Structure
    - Planned features (e.g., combined flags, subcommands) can be added without major refactoring

## 📈 Development Notes

Progress and development insights are tracked in `progress-log.md`.

## 🔮 Inspiration

This project is inspired by the design of the CLI11 library: (https://github.com/CLIUtils/CLI11)