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

## Day 4 (Apr 9, 2026): Basic Parsing

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