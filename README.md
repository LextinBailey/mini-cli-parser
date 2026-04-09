# Mini CLI Parser

## 📝 Overview

This project is a mini command-line interface (CLI) parser written in C++. It is inspired by the design and architecture of CLI11.

## 🎯 Goal

The goal is to get a deep understanding of how CLI parsing works by implementing my own version.

## 💡 Motivation

I wanted to learn how to read code and internalize it, so I chose the CLI11 library as my first project to study. To reinforce what I learned, I'm going to rebuild a my own version from scratch.

Main focuses of this project:
- Converting theory into implementation
- Understanding how arguments are parsed and mapped
- Practicing clean C++ design habits

## 🎓 What I Learned from CLI11

- The power of clean API design
- Separating concerns between App and Option
- Mapping raw argv input to structured data

## 🧱 Features (Planned)

- [ ] Examples
- [ ] Combined short flags

## 📌 Features (Implemented)

- [x] Register CLI options
- [x] Parse argv input
- [x] Store and retrieve values
- [x] Print parsed results
- [x] Help menu
- [x] Error handling
- [x] Short flags
- [x] Required options

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

## 📈 Progress Log

See `progress-log.md` for daily updates.

## 🔮 Inspiration

- CLI11 (https://github.com/CLIUtils/CLI11)