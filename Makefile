# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/18 18:04:44 by ade-sede          #+#    #+#              #
#    Updated: 2017/05/18 17:53:39 by ade-sede         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
LIB_DIR = libft
LIBFT_INCLUDE = $(LIB_DIR)/includes
INCLUDE_DIR = includes
SRC_DIR = srcs

# Flags at compile time
CFLAGS = -g -Wall -Wextra -Werror
CC = gcc

# Sources
SRC_FILE =	\
	main.c \
	main_loop.c \
	exec_bin.c \
	return_failure.c \
	env/environ.c \
	env/load_base_env.c \
	env/edit_env.c \
	env/path.c \
	env/t_env.c \
\
	builtin/cd.c \
	builtin/echo.c \
	builtin/env.c \
	builtin/setenv.c \
	builtin/unsetenv.c \
	builtin/exit.c \
	builtin/exec_builtin.c \

SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILE:.c=.c))

all: $(NAME) LIB

LIB:
	@make -C $(LIB_DIR) re

$(NAME):
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) -L $(LIB_DIR) -lft -I $(LIBFT_INCLUDE) -I $(INCLUDE_DIR)

clean:
	@/bin/rm -rf $(OBJ)

fclean:clean
	@/bin/rm -rf $(NAME)

re: fclean LIB all
