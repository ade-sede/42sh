# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/18 18:04:44 by ade-sede          #+#    #+#              #
#    Updated: 2017/05/17 20:45:30 by ade-sede         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
LIB_DIR = libft
INC_DIR = $(LIB_DIR)/includes
SRC_DIR = srcs

# Flags at compile time
CFLAGS = -g -Wall -Wextra -Werror
CC = gcc

# Sources
SRC_FILE =	\
	main.c \
	return_failure.c \
	env/environ.c \
	env/setenv.c \
	env/load_base_env.c \
	env/unsetenv.c \
	env/path.c \
	builtin/cd.c

SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILE:.c=.c))

all: $(NAME) LIB

LIB:
	@make -C $(LIB_DIR) re

$(NAME):
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) -L $(LIB_DIR) -lft -I $(INC_DIR)

clean:
	@/bin/rm -rf $(OBJ)

fclean:clean
	@/bin/rm -rf $(NAME)

re: fclean LIB all
