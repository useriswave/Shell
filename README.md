# C Shell

A simple Unix-like shell written in C.

## Features

- Reads user input
- Splits input into command arguments
- Runs external programs
- Supports basic shell loop behavior
- Uses process creation and execution with C system calls

## Project Structure

```text
.
├── Makefile
├── README.md
├── .gitignore
└── src
    ├── main.c
    ├── shell.c
    └── shell.h
```

## Build

```bash
make
```

## Run

```bash
./shell
```

or:

```bash
make run
```

## Clean

```bash
make clean
```
