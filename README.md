# minishell

> **42 cursus** · C · a small shell, the way bash works.

A simplified shell that parses and executes command lines: handling pipes, redirections, environment variables, quotes and a set of built-in commands.

## Features

- Command parsing with single/double quotes and escaping
- Pipes `|` and redirections `<`, `>`, `>>`, `<<` (heredoc)
- Environment variable expansion (`$VAR`, `$?`)
- Builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)

## Build

```bash
make        # builds minishell (uses readline)
```

## Usage

```bash
./minishell
minishell$ ls -la | grep .c > out.txt
minishell$ echo $USER
```

## Key concepts

Process creation (`fork`, `execve`, `wait`), file descriptors, pipes and parsing.

---

*42 cursus project — [github.com/rjacquet31](https://github.com/rjacquet31)*
