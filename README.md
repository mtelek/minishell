# Minishell

[![Status](https://github.com/mtelek/minishell/actions/workflows/build.yml/badge.svg)](https://github.com/mtelek/minishell/actions/workflows/build.yml)
[![Code Size](https://img.shields.io/github/languages/code-size/mtelek/minishell?style=flat-square)](https://github.com/mtelek/minishell)
![Project Score](https://img.shields.io/badge/Minishell-93%25-brightgreen)

## Project Description ✨

Minishell is a minimalist Unix shell implementation created as part of the 42 school curriculum. This project teaches the fundamentals of process creation, file descriptors, and shell programming by recreating a functional shell with many of Bash's core features.

Key features include:
- Command execution with PATH resolution
- Environment variable expansion
- Redirections (`>`, `>>`, `<`, `<<`)
- Pipes (`|`)
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
- Built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
- Single and double quote handling

## Installation 🛠️

### Prerequisites
- GCC compiler
- GNU Make
- readline library (install with `brew install readline` on macOS or `sudo apt-get install libreadline-dev` on Ubuntu)

### Compilation
```bash
git clone https://github.com/mtelek/minishell.git
cd minishell
make
```

This will create an executable named `minishell`.

## Usage 🚀

Run the shell with:
```bash
./minishell
```

You'll see a prompt where you can enter commands just like in Bash.

To exit, either:
- Type `exit`
- Or press `Ctrl-D`

## Testing 🧪

Here's how Minishell compares to Bash in various scenarios:

### Command Comparison Table

| Test Case | Bash Output | Minishell Output | Status |
|-----------|-------------|------------------|--------|
| `echo "Hello $USER"` | `Hello username` | `Hello username` | ✅ |
| `ls > file.txt` | Creates file | Creates file | ✅ |
| `cat < file.txt` | File contents | File contents | ✅ |
| `sleep 5 & Ctrl-C` | New prompt | New prompt | ✅ |
| `echo -n "No newline"` | No newline | No newline | ✅ |
| `cd /tmp && pwd` | `/tmp` | `/tmp` | ✅ |
| `export TEST=value` | Sets variable | Sets variable | ✅ |
| `unset TEST` | Removes variable | Removes variable | ✅ |
| `exit 42` | Exits with 42 | Exits with 42 | ✅ |
