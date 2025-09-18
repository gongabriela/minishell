# minishell

Welcome to minis(hell)! A true milestone in someone's journey at 42, this is the first really complex project: a small shell implementation in C.
It is also the first collaborative project of the curriculum - I did it with the wonderful Drica!!!!

## Contributors

<p align="center">
  <a href="https://github.com/gongabriela">
    <img src="https://github.com/gongabriela.png" width="100px" style="border-radius:50%;" />
  </a>
  <a href="https://github.com/dricadias">
    <img src="https://github.com/dricadias.png" width="100px" style="border-radius:50%;" />
  </a>
</p>

<p align="center">
  <a href="https://github.com/gongabriela">Gabriela Gonçalves</a> · 
  <a href="https://github.com/dricadias">Andrielly Dias</a>
</p>

---

## Table of Contents

- [About](#about)  
- [Features](#features)  
- [Requirements](#requirements)  
- [Installation](#installation)  
- [Usage](#usage)  
- [Built-in Commands](#built-in-commands)  
- [Project Structure](#project-structure)  

---

## About

**minishell** is a minimal Unix shell developed for the 42 school project.  
It aims to replicate basic shell behavior, handling command parsing, execution, redirections, pipes, built-ins, environment variables, etc.

---

## Features

- Parse commands with arguments  
- Handle environment variables  
- Implement built-in commands (`cd`, `echo`, `export`, `unset`, `pwd`, `exit`)  
- Manage input/output redirections (`>`, `<`, `>>`, `<<`)  
- Pipe support (`|`)  
- Support for quoted strings and escaping  
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)

---

## Requirements

- Compiler: `gcc`  
- OS: Unix / Linux / macOS  
- Libraries:  
  - `readline` (if used)  
  - Standard C library  

---

## Installation

```bash
# Clone the repo
git clone https://github.com/gongabriela/minishell.git
cd minishell 
```

# Build
make

## Usage

After building:
```bash
./minishell
```

You can then type commands as in a normal shell. Example:

```bash
$ echo Hello world
Hello world
$ cd /path/to/somewhere
$ pwd
/path/to/somewhere
$ ls -l | grep txt > output.txt
```
To exit:
```bash
$ exit
```
## Built-in commands

| Command  | Description                  |
| -------- | ---------------------------- |
| `cd`     | Change directory             |
| `echo`   | Display a line of text       |
| `pwd`    | Print working directory      |
| `export` | Set environment variables    |
| `unset`  | Remove environment variables |
| `exit`   | Exit the shell               |

## Project structure

```text
minishell/
├── inc/           # Header files
├── libft/         # Utility functions (libft)
├── src/           # Source files
├── Makefile       # Build configuration
├── readline.supp  # Supplement for readline usage
└── .gitignore
```
