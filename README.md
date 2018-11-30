# Assignment 2: RShell
 
**This project is a simple implementation of a bash developed from scratch.**

## Usage
Commands will have the following format:

```
$ executable [argumentList] [connector] [cmd] ...
```

Where there can be any number of commands seperated by either `||`, `&&`, or `;` which are the only valid connectors. The executable can be any executable program located at one of the PATH environmental variable locations (and argumentList is a list of zero or more arguments separated by spaces). The connector is an optional way you can run multiple commands at once. If a command is followed by `;`, then the next command is always executed; if a command is followed by `&&`, then the next command is executed only if the first one succeeds; if a command is followed by `||`, then the next command is executed only if the first one fails. The connectors do not impose any precedence and the command line should be execute from left to right. For example:

```bash
$ ls -a
$ echo hello
$ mkdir test
```

is equivalent to: 

```bash
$ ls -a; echo hello; mkdir test
```
Parentheses are also functional in this program. For example: `((echo hi && ls || pwd) && (echo hello || ls)) && exit`
  
## Known Bugs
Command `cd` will not work  
`echo hello world &&` will not ask for further input  
Anything after a # will be a comment, so if you have a command like `echo #`, the '#' will not print  
Up arrow will not remember previous commands  
Tabs will not autocomplete  
