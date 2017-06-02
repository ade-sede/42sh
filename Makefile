NAME = minishell
LIB_DIR = libft
LIBFT_INCLUDE = $(LIB_DIR)/includes
INCLUDE_DIR = includes
SRC_DIR = srcs
OBJ_DIR = objs

# Flags at compile time
SANITIZER = #-fsanitize=address -fno-omit-frame-pointer #&& ASAN_OPTIONS=symbolize=1 ASAN_SYMBOLIZER_PATH=$USER/.brew/opt/llvm/bin/llvm-symbolizer
CFLAGS = -g -Wall -Wextra -Werror
LDFLAGS = -ltermcap -L $(LIB_DIR) -lft 
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
	env/prompt.c \
\
	builtin/cd.c \
	builtin/env.c \
	builtin/setenv.c \
	builtin/unsetenv.c \
	builtin/exit.c \
	builtin/exec_builtin.c \
	builtin/echo.c \
	builtin/history.c \
	builtin/history_handle_options.c \
\
	exec/exec_bin.c \
	exec/main_loop.c \
	exec/expand_args.c \
	exec/signals.c \
\
	line_editing/conf_term.c \
	line_editing/edit_del.c \
	line_editing/edit_move.c \
	line_editing/get_input.c \
	line_editing/edit_init.c \
	line_editing/edit_refresh.c \
	line_editing/put_termcap.c \
	line_editing/edit_add.c \
	line_editing/edit_signals.c \
	line_editing/edit_move_cursor.c \
	line_editing/edit_exit.c \
	line_editing/edit_insert_str.c \
	line_editing/copy_paste.c \
\
	completion/comple_exit_matched.c \
	completion/comple_init.c \
	completion/comple_signals.c \
	completion/comple_get_input.c \
	completion/comple_refresh.c \
	completion/size_term.c \
	completion/comple_move.c \
	completion/comple_matches.c \
\
	history/load_history.c \
	history/history_move.c \
	history/history_init.c \
	history/history_refresh.c \
	history/history_move_loop.c \
	history/btsearch_refresh.c \
	history/btsearch_exit.c \
	history/btsearch_get_input.c \
	history/btsearch_init.c \
	history/btsearch_add.c \
	history/btsearch_move.c \
\
	lexer/lexer.c \
	lexer/init.c

SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILE:.c=.c))

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC_FILE:.c=.o))

all: $(NAME)

$(NAME): create_dir $(OBJS)
	make -C ./libft/
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME) $(SANITIZER)
	
create_dir:
	@/bin/mkdir -p $(OBJ_DIR)
	@/bin/mkdir -p $(OBJ_DIR)/builtin
	@/bin/mkdir -p $(OBJ_DIR)/exec
	@/bin/mkdir -p $(OBJ_DIR)/env
	@/bin/mkdir -p $(OBJ_DIR)/line_editing
	@/bin/mkdir -p $(OBJ_DIR)/completion
	@/bin/mkdir -p $(OBJ_DIR)/history
	@/bin/mkdir -p $(OBJ_DIR)/lexer

clean:
	make clean -C ./libft/
	/bin/rm -rf objs

fclean: clean
	/bin/rm -f ./libft/libft.a
	/bin/rm -f $(NAME)

re: fclean all

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(LIBFT_INCLUDE) -I $(INCLUDE_DIR) -c -o $@ $< $(SANITIZER)

test: all
	$(CC) $(CFLAGS) $(TEST_DEPS) $(TEST_FILE) $(LDFLAGS) -I $(LIBFT_INCLUDE) -I $(INCLUDE_DIR) $(SANITIZER)
	echo "Done compiling test"
	./a.out
