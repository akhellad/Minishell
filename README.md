# Minishell Project

## Introduction

This repository houses the Minishell project, a challenge from the 42 school curriculum designed to replicate the basic functionalities of a Unix shell. The project aims to deepen understanding of process creation and synchronization, exploring system calls like `fork`, `exec`, and `wait`, and handling inter-process communication. It offers an opportunity to implement a custom shell that can parse and execute commands, handle environment variables, and support pipes and redirections.

## Features

- Parsing and execution of shell commands.
- Built-in commands implementation (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`).
- Environment variable management.
- Support for pipes (`|`) and redirections (`>`, `>>`, `<`).
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`).

## Dependencies

Minishell is written in C and relies on the following:

- GCC or Clang compiler.
- Make (for compiling).
- Readline library.
- A Unix-based operating system (Linux or MacOS).

## Installation

To compile Minishell, follow these steps:

1. Clone the repository to your local machine:

```bash
git clone git@github.com:akhellad/Minishell.git
```

2. Navigate to the cloned directory:

```bash
cd minishell
```

3. Compile the project:

```bash
make
```

This will create the `minishell` executable, ready for you to run and explore.

## Usage

To launch Minishell, execute the following command in your terminal:

```bash
./minishell
```

You will be presented with a prompt where you can enter various shell commands, experiencing the functionalities implemented in Minishell, such as command execution, environment variable management, and support for pipes and redirections.

## Example

Here's a simple example of using Minishell to list directory contents and then exit:

```bash
$> ./minishell
minishell> ls -l
minishell> exit
```

## Credits

This project was developed by Ahmed Khelladi, a student at Ecole 42. It represents a comprehensive effort to understand and replicate the workings of a Unix shell, focusing on process management, signal handling, and user interaction.
