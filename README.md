# Simple-Shell
## Overview
The simple shell is our own basic recreation of the Linux systems shell programs like the sh, bash, zsh between others, that let the user interact with basic commands. The simple shell is a command interpreter that promt you with a user interface to communicate with the operative system.
## Usage
### Compiling
```gcc -Wall -Werror -Wextra -pedantic *.c -o hsh```
### Execution
```./hsh ```
## Output
The program output will be the execution of basic programs found in the PATH in which there is a set of directories where executable programs are located based on the user's input, whether if it was in an interactive or non-interactive mode, to exit just type "exit" after the command promt or press Ctrl + D.
## Examples
Example of the interactive mode with the full path and only program name:
```
#input with full path
$ /bin/ls

#expected output
main.c shell.h print_error.c non_interactive.c man_1_simple_shell interactive.c input_format.c get_env.c env_linked_list.c

#input with program name
$ ls

#expected output
main.c shell.h print_error.c non_interactive.c man_1_simple_shell interactive.c input_format.c get_env.c env_linked_list.c

$ exit
$
```
Example of the non-interactive mode:
```
#input

$ echo "/bin/ls" | ./hsh

#output

main.c shell.h print_error.c non_interactive.c man_1_simple_shell interactive.c input_format.c get_env.c env_linked_list.c
$
```
## Authors
**Juan Urbano**
**Adrian Hernandez**