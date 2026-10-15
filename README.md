# Mini Grep

A simplified implementation of the Linux `grep` utility written in modern C++.

## Features

- Search text in files
- Recursive directory search
- Case-insensitive search
- Search multiple files
- Line numbers in output
- Standard input search; connected via pipes

## Project Structure

```text
project/
│
├── .gitignore
├── LICENSE
├── Makefile
├── README.md
│
├── include/
│   ├── cli.hpp
│   ├── core.hpp
│   ├── matcher.hpp
│   └── output.hpp
│   ├── traversal.hpp
│   └── utils.hpp
|
├── src/
│   ├── cli.cpp
│   ├── core.cpp
│   ├── main.cpp
│   ├── matcher.cpp
│   └── output.cpp
│   ├── traversal.cpp
│   └── utils.cpp
│
└── text.txt
```

## Requirements

- C++17 or later
- GNU Make
- A C++ compiler such as GCC or Clang
- Linux or WSL

## Build

Clone the repository and run:

```bash
make
```

The executable will be generated at:

```text
build/my_clt
```

## Usage

Search a file:

```bash
./build/my_clt <pattern> <file_path>
```

Search recursively through a directory:

```bash
./build/my_clt -r <pattern> <directory_name>
```
Search from standard input:

```bash
<command> | ./build/my_clt <pattern>
```


## Cleaning the Build

```bash
make clean
```

## Future Improvements

- Add support for more grep flags
- Add regular expression support
- Add unit tests
- Improve error handling
- Introduce CMake

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.