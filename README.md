# Custom UNIX Shell in C

A modular UNIX-like shell built in C using Linux system calls.
This project was developed to understand process management, pipes, redirection, signals, and shell internals in Linux.

---

# Features

## Command Execution

* Execute Linux commands using `fork()`, `execvp()`, and `waitpid()`

Example:

```bash
ls
pwd
top
```

---

## Pipes

Supports multiple piped commands using `pipe()` and `dup2()`.

Example:

```bash
ls | wc
cat file.txt | grep hello
```

---

## Input and Output Redirection

### Output Redirection

```bash
ls > output.txt
```

### Append Redirection

```bash
echo hello >> file.txt
```

### Input Redirection

```bash
wc < file.txt
```

---

## STDERR Redirection

### Error Redirection

```bash
ls invalid 2> error.txt
```

### Append STDERR

```bash
ls invalid 2>> error.txt
```

### Redirect STDERR to STDOUT

```bash
ls invalid > out.txt 2>&1
```

---

## Background Processes

Supports background execution using `&`.

Example:

```bash
top &
```

---

## Built-in Commands

Currently implemented:

* `cd`

Example:

```bash
cd Desktop
```

---

## Signal Handling

* Handles:

  * `SIGINT`
  * `SIGTSTP`
  * `SIGQUIT`

The shell ignores signals while child processes use default behavior.

---

## Modular Project Structure

```text
myshell/
│
├── include/
│   ├── builtins.h
│   ├── config.h
│   ├── executor.h
│   ├── jobs.h
│   ├── parser.h
│   └── redirect.h
│
├── src/
│   ├── builtins.c
│   ├── executor.c
│   ├── jobs.c
│   ├── parser.c
│   └── redirect.c
│
├── shell.c
├── Makefile
└── README.md
```

---

# Technologies Used

* C Programming
* Linux
* GCC
* UNIX System Calls
* Makefile

---

# Concepts Learned

* Process Creation
* File Descriptors
* Pipes
* Redirection
* Signals
* Inter-Process Communication
* Modular Software Design
* Shell Internals

---

# Build Instructions

## Compile

```bash
make
```

---

## Run

```bash
./myshell
```

---

## Clean Build Files

```bash
make clean
```

---

# Example Usage

```bash
ls | wc > output.txt
```

```bash
cat file.txt | grep hello
```

```bash
top &
```

---

# Future Improvements

* Quoted string parsing
* Command history navigation
* Tab auto-completion
* Environment variable support
* Networking utilities
* Job control
* Custom shell prompt

---

# Author

Shridatta Dixit
BMS College of Engineering (BMSCE)
Computer Science and Engineering
