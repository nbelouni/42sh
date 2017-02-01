NAME = 42sh
CC = gcc
CC_FLAGS = -Wall -Werror -Wextra
LIB = -L./libft -lft -lcurses
INC = -I./inc -I./libft/inc

SRC = main.c			\
	  read.c			\
	  buf.c				\
	  term.c
SRC_DIR = ./src/
SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJ = $(SRC:.c=.o)
OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

.SILENT:

all: $(NAME)

lib:
	make -C libft

$(NAME): lib
	echo "Compiling $(NAME)"
	$(CC) -c $(SRCS) $(CC_FLAGS) $(INC)
	mkdir -p $(OBJ_DIR)
	mv $(OBJ) $(OBJ_DIR)
	$(CC) -o $@ $(OBJS) $(CC_FLAGS) $(INC) $(LIB)

clean:
	echo "Delete all object files"
	make -C libft clean
	rm -rf $(OBJ_DIR)

fclean: clean
	echo "Delete objects and binary"
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all
