# minishell

## Info

A simpler version of shell in C.

- Grade: 100/100
- Keywords: Unix logic
- Skills: Imperative programming/ Rigor/ Unix

## Minishell can

- Have a working history.
- Search and launch the right executable of commands (based on the PATH variable or using a relative or an absolute path).
- Handle `’` which should prevent the shell from interpreting the metacharacters in the quoted sequence.
- Handle `"` which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
- Handle redirections `>`, `<`, `>>`, `<<`.
- Handle pipes `|`. The output of each command in the pipeline is connected to the input of the next command via a pipe.
- Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
- Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
- Handle `ctrl-C`, `ctrl-D` and `ctrl-\`
- Handle builtins:
  - `echo` with option -n
  - `cd` with only a relative or absolute path
  - `pwd` with no options
  - `export` with no options
  - `unset` with no options
  - `env` with no options or arguments
  - `exit` with no options

## How to use

- Clone and cd to the repo

- Compile with make

- Execute `minishell` 

```sh
./minishell
```

- Interact with it
