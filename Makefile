
NAME = 42sh

IDIR = ./inc/
ILIB = ./libft/inc
INCS = 42sh.h		\
	   read.h		\
	   lex.h		\
	   exec.h		\
	   completion.h	\
	   globbing.h	\
		job.h	\
	  	hash.h	\
	  	list.h	\
	  	io.h
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
		ft_builtin_export.c	\
		ft_builtin_export_tools.c\
		ft_builtin_unset.c\
		ft_export_print.c\
		ft_norm_tools.c		\
		ft_init.c			\
		ft_list_tools.c		\
		ft_list_tools2.c	\
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
		reg_path.c			\
		lex_buf_line.c		\
		lex_buf_pars.c		\
		is_tok.c			\
		is_check.c			\
		sort_list.c			\
		sort_list_token.c	\
		sort_list_token2.c	\
		can_create_tree.c	\
		completion.c		\
		is_token_type.c		\
		return_errors.c		\
		ast_create.c		\
		find_quote_end.c	\
		globbing.c			\
		here_doc.c			\
		replace_expansions.c\
		find_expansions.c	\
		exp.c				\
		which_sequence_type.c\
		expand_text.c		\
		replace_regex.c		\
		check_regex.c		\
		match_regex.c		\
		find_regex.c		\
		expand.c			\
		job.c				\
		job_redir.c			\
		is_local_var.c		\
		ft_print.c			\
		hash.c				\
		list.c				\
		io.c				\
		handle_jobs.c		\
		init_shell.c		\
		create_cmd_for_job.c\
		ft_get_history.c	\
		ft_set_history.c	\
		ft_histopt_filename.c\
		ft_histopt_offset.c	\
		ft_histopt_args.c	\
		ft_history_opt.c	\
		ft_history_tools.c	\
		ft_builtin_history.c\
		ft_builtin_bang.c	\
		ft_builtin_bg.c	\
		ft_builtin_fg.c	\
		ft_builtin_jobs.c	\
		ft_default_set.c	\
		ft_bang_alphanum_sub.c\
		ft_bang_special_sub.c\
		ft_bang_substitution.c\
		ft_quick_substitution.c\
		combine_cmd.c		\
		edit_history.c		\
		extra_builtins.c

SRCC = $(addprefix $(SDIR),$(SRCS))

ODIR = ./obj/
OBJS = $(SRCS:.c=.o)
OBCC = $(addprefix $(ODIR),$(OBJS))

FLAG =  -Wall -Werror -Wextra -DDEBUG_F  #-g -fsanitize=address -UTOSTOP

$(NAME): $(OBCC)
	make -C ./libft/
	gcc -v $(FLAG) $(OBCC) -ltermcap -L$(LDIR) $(LIBS) -o $(NAME)

$(ODIR)%.o: $(SDIR)%.c Makefile
	@mkdir -p $(ODIR)
	gcc $(FLAG) -c $< -o $@ -I$(IDIR) -I$(ILIB)

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
