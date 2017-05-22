# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/18 18:04:44 by ade-sede          #+#    #+#              #
#    Updated: 2017/05/22 16:52:55 by vcombey          ###   ########.fr        #
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
	return_failure.c \
\
	env/environ.c \
	env/load_base_env.c \
	env/add_var.c \
	env/remove_var.c \
	env/t_env.c \
\
	builtin/cd.c \
	builtin/env.c \
	builtin/setenv.c \
	builtin/unsetenv.c \
	builtin/exit.c \
	builtin/exec_builtin.c \
\
	exec/exec_bin.c \
	exec/main_loop.c \
\
	line_editing/conf_term.c \
	line_editing/edit_del.c \
	line_editing/edit_move.c \
	line_editing/get_input.c \
	line_editing/line_editing.c \
	line_editing/put_termcap.c \
\
	completion/comple_exit_matched.c \
	completion/comple_init.c \
	completion/comple_loop.c \
	completion/comple_refresh.c \
	completion/size_term.c \
	completion/comple_move.c \

SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILE:.c=.c))

OBJS = $(addprefix objs/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft/
	$(CC) -g $(OBJS) -L libft  -ltermcap -lft -o $(NAME)

clean:
	make clean -C ./libft/
	/bin/rm -rf objs

fclean: clean
	/bin/rm -f ./libft/libft.a
	/bin/rm -f $(NAME)

re: fclean all

objs/%.o : %.c
	@/bin/mkdir -p objs
	@/bin/mkdir -p objs/srcs
	@/bin/mkdir -p objs/srcs/builtin
	@/bin/mkdir -p objs/srcs/exec
	@/bin/mkdir -p objs/srcs/env
	@/bin/mkdir -p objs/srcs/line_editing
	@/bin/mkdir -p objs/srcs/completion
	gcc -g $(CFLAGS) -I $(LIBFT_INCLUDE) -I $(INCLUDE_DIR) -c -o $@ $<
