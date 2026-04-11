# Progress Log

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
    - Added `parse()` logic to detect registered options
    - Flags like `--verbose` are now recognized and marked as set
    - Simple test in main
```bash
$ ./build/app --verbose
Verbose ON
```
- Implemented value parsing for CLI options
    - Options that expect values now take the next argument
    - Handles basic validation:
        - Out of bounds check (no next argument)
        - Next argument not a value
- Added error handling for CLI parsing
    - Throws exceptions for:
        - Unknown options
        - Missing values
        - Invalid values
    - Wrapped parsing in try/catch inside main
- Added `--help` option and help menu
    - `--help` displays option names and descriptions
    - Current spacing is fixed. Dynamic spacing planned in the future
- Made help menu a top-level concern
    - Checked for `--help` first in main
    - If found: print help menu: exit
    - Else: parse normally
    - This ensures help is never blocked by errors and will always give guidance to the user
- Updated `README.md` with implemented features and planned features
- Added support for short flags
    - Option skeleton now includes `short_name`
    - `add_option()` now accepts short flags
    - `parse()` handles short flags
    - Help menu prints both forms
    - Example: `--name` or `-n`
- Added support for required CLI options
    - `validate_required()` after parsing
    - Help menu indicates required options

## Day 5 (Apr 10, 2026): README Update, Combined Short Flags, Separation of Concerns, Help Menu Adjustment, Short Flag Lookup

- Updated `README.md` to demonstrate and explain: purpose, example usage, and internal workings
- Added support for combined short flags (e.g., `-vn John`)
    - Options requring value must be last in the group
- Separated parsing flow, option resolution, and value handling
    - Previous `parse()` handled all these concerns
    - Added helper functions: `resolve_option()` and `handle_value()`
    - Now `parse()` calls `resolve_option()` and `handle_value()` (when necessary)
    - This keeps parsing flow clean
- Moved `print_help()` call:
    - After parsing
    - When an exception is caught and `--help` has been set
- Improved short flag lookup from O(n) to O(1)
    - Before was looping through each `Option`
    - This became slow when I added support for combined short flags
    - To fix this, I implemented a second hash map that maps short names directly to their corresponding `Option` objects
    - I used structured binding, which is a C++17 feature
        - There is a workaround for C++11 compability, but for the purpose of this project, I chose the cleaner, modern approach

## Day 6 (Apr 11, 2026): CMake

- Implemented CMake and updated `README.md` build and usage instructions