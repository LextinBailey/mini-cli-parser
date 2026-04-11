# Progress Log

A day-by-day log of development decisions, features, and design evolution.

## Day 1 (Apr 6, 2026): GitHub Repo

- Created GitHub repository
- Planned project structure

## Day 2 (Apr 7, 2026): Project Setup

- Set up project structure
- Wrote initial README

## Day 3 (Apr 8, 2026): Designing Interfaces

- Designed `Option` and `App` class interfaces
- `Option.hpp` defines `Option` class
- `App.hpp` defines `App` class with `add_option()`, `parse()`, `get_option()`

## Day 4 (Apr 9, 2026): Basic Parsing, Validation, Help Menu, Features: Short Flags and Required Options

- Implemented basic CLI parsing for flags
    - Registered options are deteced and marked as set
```bash
$ ./build/app --verbose
Verbose ON
```
- Implemented value parsing for CLI options
    - Supports next-argument values with validation (bounds + flag detection)
- Added error handling for CLI parsing
    - Throws exceptions for unknown options, missing values, and invalid values
    - Wrapped parsing in try/catch inside main
- Added `--help` option and help menu
    - `--help` displays option names and descriptions
    - Current spacing is fixed. Dynamic spacing planned in the future
- Made help menu a top-level concern
    - This ensures help is never blocked by errors and will always give guidance to the user
    - Later reversed this decision after refining error-handling flow
- Updated `README.md` with implemented features and planned features
- Added support for short flags
    - `add_option()` now accepts short flags and `parse()` now handles them
    - Help menu prints both forms (`--name`, `-n`)
- Added support for required CLI options
    - `validate_required()` after parsing
    - Help menu indicates required options

## Day 5 (Apr 10, 2026): README Update, Combined Short Flags, Separation of Concerns, Help Menu Adjustment, Short Flag Lookup

- Updated `README.md` to demonstrate and explain: purpose, example usage, and internal workings
- Added support for combined short flags (e.g., `-vn John`)
    - Options requiring a value must be last in the group
- Separated parsing flow, option resolution, and value handling
    - `parse()` calls `resolve_option()` and `handle_value()` (when necessary) to keep parsing flow clean
- Moved `print_help()` call:
    - After parsing and when an exception is caught and `--help` has been set
- Improved short flag lookup from O(n) to O(1)
    - Before was looping through each `Option` and this became slow when I added support for combined short flags
    - Implemented a second hash map that maps short names directly to their corresponding `Option` objects
- Used structured bindings (C++17)
    - There is a workaround for C++11 compability, but for the purpose of this project, I chose the cleaner, modern approach

## Day 6 (Apr 11, 2026): CMake, Library Structure

- Implemented CMake and updated `README.md` build and usage instructions
- Restructured design as a header-only library
    - `mini_cli`: reusable library
    - `example_app`: demo program
    - `target_link_libraries`: connects them
- Now can be included in other projects:
```cpp
#include "mini_cli/App.hpp"
```