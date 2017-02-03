NAME = 42sh

IDIR = ./inc/ 
ILIB = ./libft/inc
INCS = 42sh.h	\
	   read.h
INCC = $(addprefix $(IDIR), $(INCS))

LDIR = ./libft
LIBS = -lft

SDIR = ./src/
SRCS = main.c			\
	   read.c			\
	   buf.c			\
	   term.c			\
	   signal.c			\
	   curs.c			\
	   edit_move.c		\
	   edit_buf.c		\
	   edit_line.c		\
	   edit_visual.c

SRCC = $(addprefix $(SDIR),$(SRCS))

ODIR = ./obj/
OBJS = $(SRCS:.c=.o)
OBCC = $(addprefix $(ODIR),$(OBJS))

FLAG = -g -Wall -Werror -Wextra

$(NAME): $(OBCC)
	make -C ./libft/
	gcc $(FLAG) $(OBCC) -ltermcap -L$(LDIR) $(LIBS) -o $(NAME)

$(ODIR)%.o: $(SDIR)%.c
	@mkdir -p $(ODIR)
	gcc $(FLAG) -c $^ -o $@ -I$(IDIR) -I$(ILIB)

all: $(NAME)

clean:
	echo "Delete all object files"
	@make -C ./libft/ clean
	/bin/rm -rf $(ODIR)

fclean: clean
	echo "Delete objects and binary"
	@make -C ./libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all

