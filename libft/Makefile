# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/05 17:19:47 by nbelouni          #+#    #+#              #
#    Updated: 2017/04/10 19:42:28 by alallema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a
CC= gcc
CFLAGS= -Wall -Werror -Wextra # -g -fsanitize=address
INC=  -I./inc
OBJ=ft_bzero.o ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o\
	ft_isprint.o ft_memccpy.o ft_memchr.o ft_memcmp.o ft_memcpy.o\
	ft_memmove.o ft_memset.o ft_putstr.o ft_strcat.o ft_strchr.o ft_strcmp.o\
	ft_strcpy.o ft_strdup.o ft_strlcat.o ft_strlen.o ft_strncat.o\
	ft_strncmp.o ft_strncpy.o ft_strnstr.o ft_strrchr.o ft_strstr.o\
	ft_tolower.o ft_toupper.o ft_atoi.o ft_memalloc.o ft_memdel.o\
	ft_strnew.o ft_strdel.o ft_strclr.o	ft_striter.o ft_striteri.o\
	ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o\
	ft_strjoin.o ft_strtrim.o ft_strsplit.o ft_itoa.o ft_putchar.o\
	ft_putendl.o ft_putnbr.o ft_putchar_fd.o ft_putstr_fd.o ft_putnbr_fd.o\
	ft_putendl_fd.o ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o\
	ft_lstiter.o ft_lstmap.o get_next_line.o ft_print_error.o \
	ft_is_valid_dir.o ft_get_index_of.o ft_strcut.o ft_strisdigit.o\
	ft_epurstr.o ft_tabconcat.o ft_puttab.o ft_tablen.o ft_multi_join.o\
	ft_multi_concat.o ft_multi_free.o ft_strlchr.o ft_free_and_dup.o\
	ft_tabdel.o ft_free_and_join.o ft_strreplace.o ft_intlen.o ft_putnchar.o\
	ft_lstpush.o ft_getopt.o

SRCS=ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c\
	 ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
	 ft_memmove.c ft_memset.c ft_putstr.c ft_strcat.c ft_strchr.c\
	 ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c\
	 ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnstr.c ft_strrchr.c\
	 ft_strstr.c ft_tolower.c ft_toupper.c ft_atoi.c ft_memalloc.c\
	 ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c\
	 ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c\
	 ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c\
	 ft_itoa.c ft_putchar.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c\
	 ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_lstnew.c\
	 ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c\
	 get_next_line.c ft_print_error.c ft_is_valid_dir.c ft_strcut.c\
	 ft_get_index_of.c ft_strisdigit.c ft_epurstr.c ft_tabconcat.c\
	 ft_puttab.c ft_tablen.c ft_multi_join.c ft_multi_concat.c\
	 ft_multi_free.c ft_strlchr.c ft_free_and_dup.c ft_tabdel.c\
	 ft_free_and_join.c ft_strreplace.c ft_intlen.c ft_putnchar.c\
	 ft_lstpush.c ft_getopt.c

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS) $(INC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: clean all
