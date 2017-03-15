NAME = 42sh

IDIR = ./inc/
ILIB = ./libft/inc
INCS = 42sh.h	\
	   read.h	\
	   job.h	\
	   lex.h
INCC = $(addprefix $(IDIR), $(INCS))

LDIR = ./libft
LIBS = -lft

SDIR = ./src/
SRCS = 	ft_builtin_cd.c		\
		ft_builtin_echo.c	\
		ft_builtin_env.c	\
		ft_builtin_exit.c	\
		ft_builtin_setenv.c	\
		ft_builtin_unsetenv.c\
		ft_bultin_export.c	\
		ft_norm_tools.c		\
		ft_init.c			\
		ft_list_tools.c		\
		ft_list_tools2.c	\
		ft_tools.c			\
		ft_opt_parse.c		\
		read.c				\
		buf.c				\
		term.c				\
		signal.c			\
		curs.c				\
		main.c				\
	    edit_completion.c	\
	    edit_move.c			\
	    edit_buf.c			\
	    edit_line.c			\
	    edit_visual.c		\
	    calc_len.c			\
	    prompt.c			\
	    is_line_ended.c		\
		is_token.c			\
		ft_exec.c			\
		ft_tokenlist.c		\
		lex_buf_line.c		\
		lex_buf_pars.c		\
		is_tok.c			\
		is_check.c			\
		sort_list.c			\
		sort_list_token.c	\
		can_create_tree.c	\
		completion.c		\
		is_token_type.c		\
		return_errors.c		\
		ast_create.c		\
		find_quote_end.c	\
		globbing.c			\
		here_doc.c			\
		ft_print.c			\
		job.c

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

#	    ft_cmdnew.c			\
#	    ft_cmdadd.c			\
#	    ft_cmdclear.c		\
#	    ft_cmdestroy.c		\
#	    ft_cmdpush.c		\
