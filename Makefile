# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/27 19:32:48 by nomargen          #+#    #+#              #
#    Updated: 2022/06/24 02:02:25 by cjanetta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra -O0 -g

SRC			=	src/buildtin_utils1.c src/buildtin_utils2.c src/buildtin_utils3.c \
				src/buildtin.c src/elem_type.c src/elem.c src/get_line_utils.c \
				src/get_line.c src/local_env_utils1.c src/local_env_utils2.c \
				src/local_env_utils3.c src/local_env.c src/minishell_utils.c \
				src/minishell.c src/parse_utils.c src/parse.c src/pipex_utils1.c \
				src/pipex_utils2.c src/pipex_utils3.c src/pipex_utils4.c src/pipex.c

HEAD		=	inc/buildtin.h inc/local_env.h inc/parse.h inc/pipex_types.h inc/pipex.h

OBJ			=	$(SRC:.c=.o)

LIBFT_DIR	=	lib/libft

LIBFT		=	$(addsuffix .a, $(LIBFT_DIR))

RM			=	rm -rf

LDLIBS		=	-lft -lreadline


%.o: %.с  
	$(CC) $(CFLAGS) -c -o $@ $<

all:	$(NAME)

$(NAME): $(HEAD) $(OBJ) $(LIBFT)
	$(CC) -g -o $(NAME) $(OBJ) -Llib $(LDLIBS)

$(LIBFT): $(LIBFT_DIR)/libft.a
	cp $(LIBFT_DIR)/libft.a $(LIBFT)

$(LIBFT_DIR)/libft.a:
	make --directory=$(LIBFT_DIR) bonus

lib_clean:
	make --directory=$(LIBFT_DIR) fclean
	$(RM) lib/libft.a

fclean: clean
	$(RM) $(NAME)

clean: lib_clean
	$(RM) $(OBJ)

re: fclean all

.PHONY: all clean fclean lib_clean re
