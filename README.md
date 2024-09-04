# Shell Simulation

This project is a simple shell simulation written in C++. It allows users to execute commands, handle pipelines, perform output redirection, and more. Below is a detailed guide on how to use and understand the code provided.

## Features

- **Command Execution**: Execute basic commands like `echo`, `pwd`, `cd`, `ls`, `search`, `history`, `pinfo`, and custom commands.
- **Pipelines**: Handle commands with pipelines (`|`).
- **Redirection**: Redirect output to a file using the `>` operator.
- **Signal Handling**: Gracefully handle interrupts and stop signals.

## Structure

### Source Files

1. **driver.cpp**
   - Contains the main function and core logic of the shell.
   - Includes various functions to handle different commands and features.

2. **cd_pwd_echo_command.cpp**
   - Functions related to `cd`, `pwd`, and `echo` commands.

3. **auto_completation_feature.cpp**
   - Contains logic for command auto-completion (implementation not provided in this snippet).

4. **history.cpp**
   - Manages command history (implementation not provided in this snippet).

5. **ls_command.cpp**
   - Implements the `ls` command to list directory contents.

6. **operators.cpp**
   - Handles operators like `>>` for output redirection (implementation not provided in this snippet).

7. **pinfo_command.cpp**
   - Provides process information (`pinfo` command) (implementation not provided in this snippet).

8. **search_command.cpp**
   - Implements the `search` command to search for patterns (implementation not provided in this snippet).

9. **execvp_command.cpp**
   - Executes commands using `execvp`.

10. **pipeline.cpp**
    - Manages command pipelines (implementation not provided in this snippet).

11. **redirection.cpp**
    - Handles output redirection (`>` operator).

### `driver.cpp` Overview

The `driver.cpp` file is the entry point of the shell simulation. It initializes the shell, handles user inputs, processes commands, and manages various features.

### Key Functions

- **`get_username_and_systemname(std::string& path)`**
  - Retrieves the current username and system name.
  - Updates the shell prompt with this information.

- **`process_command(std::string command, std::string input_command)`**
  - Processes and executes commands based on user input.
  - Supports basic commands and redirection.

- **`execute_pipe(std::string command)`**
  - Executes commands connected by pipes.

- **`executeCommandWithRedirection(std::string command)`**
  - Handles output redirection to a file.

- **`signal_callback_handler(int signum)`**
  - Handles signals like SIGINT (Ctrl+C) and SIGTSTP (Ctrl+Z).

## Compilation and Usage

### Compilation

You can compile the code using `g++`:

```sh
g++ -o my_shell driver.cpp cd_pwd_echo_command.cpp auto_completation_feature.cpp history.cpp ls_command.cpp operators.cpp pinfo_command.cpp search_command.cpp execvp_command.cpp pipeline.cpp redirection.cpp
```
or use Makefile to execute

```sh
make
```

```sh
./driver
```

### Running

To run the shell:

```sh
./my_shell
```

### Usage

- **Basic Commands**: Type commands like `echo`, `pwd`, `cd`, `ls`, etc.
- **Pipeline**: Use the `|` symbol to chain commands, e.g., `echo "hello" | grep "hello"`.
- **Redirection**: Use `>` to redirect output to a file, e.g., `echo "hello" > output.txt`.
- **History**: Type `history` to view recent commands. Use `history <N>` to view the last N commands.
- **Process Info**: Use `pinfo <pid>` to get information about a process.

## Error Handling

- **Signal Handling**: The shell handles interruptions and stop signals gracefully.
- **Command Parsing**: The shell provides error messages for invalid commands and input.

## Notes

- This shell simulation does not include advanced features like job control or background process management.
- Some feature implementations are assumed to be provided in separate files (`auto_completation_feature.cpp`, `history.cpp`, etc.).
