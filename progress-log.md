# Progress Log

## Day 1 (Apr 6, 2026): GitHub Repo

- Created GitHub repository
- Planned project structure

## Day 2 (Apr 7, 2026): Project Setup

- Set up project structure
- Wrote inital README

## Day 3 (Apr 8, 2026): Designing Interfaces

- Designed Option and App class interfaces
- Option.hpp defines Option class
- App.hpp defines App class with add_option(), parse(), get_option()

## Day 4 (Apr 9, 2026): Basic Parsing, Validation, Help Menu, Features: Short Flags and Required Options

- Implemented basic CLI parsing for flags
    - Added parse() logic to detect registered options
    - Flags like --verbose are now recognized and marked as set
    - Simple test in main:
        - ./build/app --verbose
        - Verbose is ON
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
- Added --help option and help menu
    - --help displays option names and descriptions
    - Current spacing is fixed. Dynamic spacing planned in the future
- Made help menu a top-level concern
    - Checked for --help first in main
    - If found: print help menu: exit
    - Else: parse normally
    - This ensures help is never blocked by errors and will always give guidance to the user
- Updated `README.md` with implemented features and planned features
- Added support for short flags
    - Option skeleton now includes short_name
    - add_option() now accepts short flags
    - parse() handles short flags
    - Help menu prints both forms
    - Example: "--name" or "-n"
- Added support for required CLI options
    - validate_required() after parsing
    - Help menu indicates required options