# Mini Grep

A simplified implementation of the Linux `grep` utility written in modern C++.

## Features

- Search text in one or more files
- Recursive directory search (`-r`)
- Case-sensitive by default, with optional case-insensitive search (`-i`)
- Fast substring matching using the Boyer-Moore-Horspool algorithm
- Line numbers in output
- Standard input search, so it works in pipes
- `--` to mark the end of options, so patterns that start with `-` can be searched
- grep-compatible exit codes for use in scripts
- Non-fatal error handling: missing paths, unreadable files and locked directories are reported to stderr and the search continues

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
│   ├── cli.hpp          # Config struct and argument parsing
│   ├── core.hpp         # Orchestrates traversal + matching
│   ├── matcher.hpp      # PatternSearcher (Boyer-Moore-Horspool)
│   ├── options.hpp      # SearchOptions (matching behaviour flags)
│   ├── output.hpp       # Result printing
│   └── traversal.hpp    # File/directory collection
│
├── src/
│   ├── cli.cpp
│   ├── core.cpp
│   ├── main.cpp
│   ├── matcher.cpp
│   ├── output.cpp
│   └── traversal.cpp
│
└── text.txt
```

## Requirements

- A C++20 compiler such as GCC or Clang
- GNU Make
- Linux, WSL, or a POSIX-style shell on Windows (e.g. MSYS2 or Git Bash), since the Makefile uses `mkdir -p` and `rm -f`

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

```text
my_clt [-r] [-i] [--] <pattern> [file ...]
```

If no files are given, input is read from standard input.

### Options

| Option | Description |
|--------|-------------|
| `-r`   | Search directories recursively |
| `-i`   | Ignore case when matching |
| `--`   | End of options; everything after it is treated as the pattern and paths |

### Examples

Search a file:

```bash
./build/my_clt <pattern> <file_path>
```

Search several files:

```bash
./build/my_clt <pattern> <file1> <file2>
```

Search recursively through a directory:

```bash
./build/my_clt -r <pattern> <directory_name>
```

Case-insensitive search:

```bash
./build/my_clt -i hello text.txt
```

Search from standard input:

```bash
<command> | ./build/my_clt <pattern>
```

Search for a pattern that starts with a dash:

```bash
./build/my_clt -- -v text.txt
```

## Exit Codes

Follows the same convention as grep:

| Code | Meaning |
|------|---------|
| `0`  | At least one line matched |
| `1`  | No lines matched |
| `2`  | An error occurred (missing path, unreadable file, unknown flag, etc.), even if some matches were found |

Example:

```bash
./build/my_clt hello text.txt
echo $?
```

## Error Handling

Errors are printed to stderr in the form `my_clt: <path>: <reason>`, and the search continues with the remaining files.

When searching recursively, directories that cannot be opened due to permissions are skipped silently, unlike GNU grep, which prints a warning for each one.

## Cleaning the Build

```bash
make clean
```

## Future Improvements

- More grep flags: `-n`, `-c`, `-l`, `-v`, `-w`, `-m`, and context lines (`-A`/`-B`/`-C`)
- Combined short flags (e.g. `-ri`)
- `-` as a path meaning standard input
- grep-style `file:line:content` output format
- Regular expression support
- Unit tests
- Introduce CMake

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.