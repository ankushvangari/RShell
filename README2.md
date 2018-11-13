# Assignment 2: Writing a Basic Command Shell

**This project *must* be done in a group of two**

## Coding Requirements
Write a command shell called rshell in C++. Your shell will perform the following steps:

1. Print a command prompt (e.g. `$`)
2. Read in a line of command(s) (and connector(s)) from standard input
3. Execute the appropriate commands using fork, execvp, and waitpid

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

Note: you can assume that there will always be a space after the semi-colon.

You are required to use the **composite pattern** when representing the commands and operators in your program. There should be no limit to the number of commands that can be chained together using the operators, and your program must be able to handle any combination of operators. For example, you should be able to handle the command:

```bash
$ ls -a; echo hello && mkdir test || echo world; git status
```

When executaing a line of commands, you will need to account for the following requirements:

1. Execute the commands using the syscalls fork, execvp, and waitpid. Previous cs100 students created two video tutorials ([a fun cartoon tutorial](https://www.youtube.com/watch?v=2c4ow5RoKA8&feature=youtu.be), [more serious explanation](https://www.youtube.com/watch?v=xVSPv-9x3gk)), and should refer to the man pages for detailed instructions.
2. Every time you run a syscall, you must check for an error condition and if an error occurs then call perror (for every syscall you use that is not error checked, you will receive an automatic -5 points). For examples on when, how, and why to use perror, see [this video tutorial](https://izbicki.me/blog/videoguide-for-github-vim-bash.html#perror).
3. You must have a special built-in command of `exit` which exits your program. This command should also adhere to the connector rules when deciding when/if it should be executed.
4. Anything that appears after a `#` character in the line should be considered a comment. For example, in the command `ls -lR /`, you would execute the program `/bin/ls` (performed using execvp) passing into it the parameters `-lR` and `/`. But in the command `ls # -lR /`, you would execute `/bin/ls`, but you would not pass any parameters because they appear in the comment section. You should also note that the `#` may or may not be followed by a space before the comment begins

**IMPORTANT:** Most bash commands are actually executables located in PATH directories such as `/bin`, `/usr/bin/` (e.g. `ls`), but some commands are built-in to bash (e.g. `cd`). So while the `ls` command should "just work" in your shell when using execvp, the `cd` command won't and isn't required to for the assignment. Only commands that can be executed through a PATH directory need to be accounted for in this assignment.

**HINT:** Pay careful attention to how you parse the command string the user enters. There are many ways to mess this up and introduce bugs into your program. You will be adding more parsing features in future assignments, so it will make your life much easier if you do it right the first time! I recommend using either the strtok function from the C standard libraries or the Tokenizer class provided in the boost library. Students often don't do this section of the assignment well and end up having to redo all of this assignment in order to complete the future assignments.

## Project Structure
You must have a directory called `src/` which contains all the source files for the project, additionally you may either have a folder `header/` which contains your header files or you may keep them in the `src/` directory. You must also have a `tests/` directory which should contain all the tests you've written using the Google Unit Test framework (the main for running the tests can be located either in `tests/` or `src/`).

Your root directory must have a CMakeLists.txt with two targest. The first target should be named `rshell` and should build the main executable and the second should be `test` which runs the unit tests that you have created using the Google Unit Test framework. 

You must have a README.md file. This file should briefly summarize your project. In particular, it must include a list of known bugs. If you do not have any known bugs, then you probably have not sufficiently tested your code! [Read this short intro](https://robots.thoughtbot.com/how-to-write-a-great-readme) to writing README files to help you. You must use the Markdown formatting language when writing your README.

Additionally you may also want to create bash scripts which send commands to rhsell in order to simualte usage by a user (integration testing). These files should be put with the Google Unit Test files in the `tests/` directory.

**IMPORTANT:** The file/directory names above are a standard convention. You must use the exact same names in your project, including capitalization.

You must also update your design document from Assignment 1 to match your implementation for this assignment. Keeping up to date documentation is one of the most ignored parts of writing software.

## Submission Instructions
You must follow the [CalTech coding guidelines](http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cppstyle.html), and your final executable should have no memory leaks.

You will also need to add a `hw2` tag to the commit that you want to be graded. git push will not automatically push tags to your repository. Use `git push origin hw2` to update your repository to include the hw2 tag. You should verify that your project builds and functions properly on hammer.cs.ucr.edu to verify that we will be able to grade it correctly.

**Do not wait to upload your assignment to Github until the project due date.** You should be committing and uploading your assignment continuously. If you wait until the last day and can't figure out how to use git properly, then you will get a zero on the assignment. NO EXCEPTIONS.

### Collaboration Policy

* You MAY NOT look at the source code of any other student.
* You MAY discuss with other students in general terms how to use the unix functions.
* You are ENCOURAGED to talk with other students about test cases. You are allowed to freely share ideas in this regard.
* You are ENCOURAGED to look at [bash's source code](https://www.gnu.org/software/bash/) for inspiration.

## Grading

|Rubric| |
|:---:|:---|
|5 pts|well commented code|
|5 pts|following style guidelines (see wiki)|
|10 pts|sufficient test cases|
|10 pts|updated design document|
|20 pts|executing single commands|
|20 pts|executing commands with connectors|
|20 pts|executing commands with comments|
|10 pts|exit commands|
|**100**|**Total**|

**IMPORTANT:** Your project structure is not explicitly listed in the grading schedule above, however not following the correct structure will result in a 20 point deduction.

**IMPORTANT:** Projects that do not correctly compile as described above will receive no points.

## Extra Credit
Many shells display extra information in the prompt besides just a simple $. For example, it is common to display the currently logged in user, and the hostname of the machine the user is logged into. If your username is jdoe001, and if you’re logged into the machine alpha023, then your prompt would look like:

```
jdoe001@alpha023$
```

You can get up to 10 points of extra credit if your prompt prints this extra information. You will need to lookup the man pages for the functions getlogin and gethostname. You must not hard code the username or hostname!
