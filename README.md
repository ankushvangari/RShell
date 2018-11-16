# Assignment 2: RShell

**This project is a simple implementation of a bash developed from scratch.**

## Usage
Commands will have the following format:

```
$ executable [argumentList] [connector] [cmd] ...
```

Where there can be any number of commands seperated by either `||`, `&&`, or `;` which are the only valid connectors. The executable can be any executable program located at one of the PATH environmental variable locations (and argumentList is a list of zero or more arguments separated by spaces). You will use the [execvp](https://linux.die.net/man/3/execvp) command to run the executable from one of the PATH locations. The connector is an optional way you can run multiple commands at once. If a command is followed by `;`, then the next command is always executed; if a command is followed by `&&`, then the next command is executed only if the first one succeeds; if a command is followed by `||`, then the next command is executed only if the first one fails. The connectors do not impose any precedence and the command line should be execute from left to right. For example:

```bash
$ ls -a
$ echo hello
$ mkdir test
```

is equivalent to: 

```bash
$ ls -a; echo hello; mkdir test
```

## Known Bugs
Command `cd` will not work
Anything after a # will be a comment, so if you have a command like `echo #`, the '#' will not print
`echo &&` does not ask for another input
