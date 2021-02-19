# Define the C compiler to use
CC = gcc

# Define the C sources files, you can use the expression $(wildcard *.c)
# SRC = binary_tree_print.c 0-binary_tree_node.c 1-binary_tree_insert_left_node.c
SRC = built_in_helpers.c built_ins.c cd2.c cd.c check_path.c env.c error_handler.c free.c _getenv.c help2.c help.c holberton.h llfuncs1.c llfuncs2.c main.c realloc.c shell.c shell_helpers.c split_string.c string_helpers1.c string_helpers2.c

# Define the name of executable
NAME = hsh

# Define the c flags compiler
CFLAGS = -g -Wall -Wextra -Werror -pedantic

# It is replacing the suffix .c of all words in the macro SRC with the .o suffix ( pattern rule)
OBJ = $(SRC:.c=.o)

# This addition first creates the macro DEPS, which is the set of .h files on which the .c files depend.
DEPS := "$(wildcard *.h)"

# the programs to delete files
RM = rm -rf

# ------------------------------------------------------------------

# These special targets are called phony and you can explicitly tell Make
# they're not associated with files, e.g.:
.PHONY : all clean oclean fclean re

# Build an executable named tree from all files
all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Delete all Emacs and Vim temporary files along with the executable
# *~ backup files
clean:
	$(RM) $(NAME) *~

# Delete the object files
oclean:
	$(RM) $(OBJ)

# deletes the Emacs temporary files, the executable, and the object files
fclean: clean oclean

# the program to delete files
re: oclean all
