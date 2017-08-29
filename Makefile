#fields ************************** DEFINING COLORS ************************************** #

COLOR_CLEAR		= \033[2K
COLOR_UP		= \033[A
COLOR_NOCOLOR	= \033[0m
COLOR_BOLD		= \033[1m
COLOR_UNDERLINE	= \033[4m
COLOR_BLINKING	= \033[5m
COLOR_BLACK		= \033[1;30m
COLOR_RED		= \033[1;31m
COLOR_GREEN		= \033[1;32m
COLOR_YELLOW	= \033[1;33m
COLOR_BLUE		= \033[1;34m
COLOR_VIOLET	= \033[1;35m
COLOR_CYAN		= \033[1;36m
COLOR_WHITE		= \033[1;37m

# **************************************************************************** #
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
	env/prompt_zsh.c \
	env/env_create_completion_tree.c \
\
	builtin/cd.c \
	builtin/env.c \
	builtin/setenv.c \
	builtin/unsetenv.c \
	builtin/exit.c \
	builtin/exec_builtin.c \
	builtin/echo.c \
\
	exec/exec_signals.c \
	exec/redir_utils.c \
	exec/exec_bin.c \
	exec/exec_operator.c \
	exec/main_loop.c \
	exec/param_expansion.c \
	exec/word_expansion.c \
	exec/tild_expansion.c \
	exec/exec_tree.c \
	exec/exec_simple_commands.c \
	exec/redir.c \
\
	lexer-parser/check_match.c \
	lexer-parser/init.c \
	lexer-parser/match_expand.c \
	lexer-parser/match_word.c \
	lexer-parser/redir.c \
	lexer-parser/start_token.c \
	lexer-parser/get_token_id.c \
	lexer-parser/lexer.c \
	lexer-parser/match_operator.c \
	lexer-parser/parser.c \
	lexer-parser/casual_node.c \
	lexer-parser/update_state.c \
	lexer-parser/free.c \
\
	line_editing/conf_term.c \
	line_editing/edit_refresh_visu.c \
	line_editing/copy_paste.c \
	line_editing/edit_add.c \
	line_editing/edit_del.c \
	line_editing/edit_exit.c \
	line_editing/edit_init.c \
	line_editing/edit_insert_str.c \
	line_editing/edit_move.c \
	line_editing/edit_move_arrows.c \
	line_editing/edit_move_cursor.c \
	line_editing/edit_refresh.c \
	line_editing/edit_signals.c \
	line_editing/get_input.c \
	line_editing/put_termcap.c \
\
	history/btsearch_add.c \
	history/btsearch_del.c \
	history/btsearch_exit.c \
	history/btsearch_get_input.c \
	history/btsearch_init.c \
	history/btsearch_move.c \
	history/btsearch_refresh.c \
	history/btsearch_signals.c \
	history/history_init.c \
	history/history_move.c \
	history/history_get_input.c \
	history/history_refresh.c \
	history/load_history.c \
\
	completion/comple_bin_matches.c \
	completion/comple_matches.c \
	completion/comple_exit_matched.c \
	completion/comple_get_input.c \
	completion/comple_init.c \
	completion/comple_file_matches.c \
	completion/comple_move.c \
	completion/comple_refresh.c \
	completion/comple_signals.c \
	completion/size_term.c \
	completion/comple_get_word_cursor.c \
	completion/ternary_search_tree.c \
	completion/ternary_search_tree_add.c \
\
	hash_table/hash.c \
	hash_table/hash_free.c \

INCLUDES_FILES = \
	builtin.h      \
	completion.h   \
	env.h          \
	exec.h         \
	hash_table.h   \
	history.h      \
	lexer.h        \
	line_editing.h \
	parser.h \

NAME ?= minishell

# Defining those variables allows auto completion to occure.
APPEND=
ASAN=
TEST_FILE=

LIB_DIR = libft
LIB_INC = -I$(LIB_DIR)/includes
LOCAL_INC = -Iincludes
SRC_DIR = srcs
OBJ_DIR = objs

ifeq ($(ASAN),yes)
	SANITIZER ?= -fsanitize=address -fno-omit-frame-pointer
endif
OPTIMIZATION ?= -O0
CFLAGS ?= -g -Wall -Wextra -Werror
CC ?= gcc
LDFLAGS = -L$(LIB_DIR) -lft -ltermcap
INCLUDES = $(LOCAL_INC) $(LIB_INC)

INCLUDES_DEP = $(addprefix ./includes/, $(INCLUDES_FILES))

SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILE:.c=.c))

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC_FILE:.c=.o))

.PHONY: all test Hello_word lib $(OBJ_DIR) $(NAME) clean fclean re

all: Hello_word lib $(OBJ_DIR) $(NAME) $(INCLUDES_DEP)
	@printf "$(COLOR_CLEAR)$(COLOR_GREEN)Successfully created $(COLOR_BLUE)$(NAME) !!!$(COLOR_NOCOLOR)\n"

Hello_word:
	@printf "$(COLOR_VIOLET)$(COLOR_UNDERLINE)Compiling$(COLOR_NOCOLOR) $(COLOR_BLUE)$(NAME) ...$(COLOR_NOCOLOR)\n"

lib:
	@make -C $(LIB_DIR) APPEND="$(APPEND)" OPTIMIZATION="$(OPTIMIZATION)" CC="$(CC)"

$(NAME): $(OBJS) 
	@printf "$(COLOR_GREEN)Successfully created objects files for binary $(COLOR_BLUE)$(NAME) !!!$(COLOR_NOCOLOR)\n"
	@printf "$(COLOR_VIOLET)Creating $(NAME) ... $(COLOR_NOCOLOR)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(INCLUDES) $(SANITIZER) $(APPEND) $(OPTIMIZATION)
	@printf "$(COLOR_UP)$(COLOR_CLEAR)"
	
$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)
	@/bin/mkdir -p $(OBJ_DIR)/builtin
	@/bin/mkdir -p $(OBJ_DIR)/exec
	@/bin/mkdir -p $(OBJ_DIR)/env
	@/bin/mkdir -p $(OBJ_DIR)/line_editing
	@/bin/mkdir -p $(OBJ_DIR)/completion
	@/bin/mkdir -p $(OBJ_DIR)/history
	@/bin/mkdir -p $(OBJ_DIR)/lexer-parser
	@/bin/mkdir -p $(OBJ_DIR)/hash_table

clean:
	@make -C $(LIB_DIR) clean
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean
	@/bin/rm -f $(NAME)

re: fclean all

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@printf "$(COLOR_VIOLET)Creating objects files for library $(COLOR_BLUE)$(NAME) ... \n$(COLOR_CYAN)"
	$(CC) $(OPTIMIZATION) $(CFLAGS) $(INCLUDES) $(SANITIZER) $(APPEND) -c -o $@ $^ 
	@printf "\n$(COLOR_NOCOLOR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)"

test: all 
	@printf "$(COLOR_VIOLET)Compiling test $(TEST_FILE) ... $(COLOR_RESET)\n"
	@$(CC) -g $(TEST_FILE) $(INCLUDES) $(LDFLAGS) $(SANITIZER) $(APPEND)
	@printf "$(COLOR_GREEN)Done !!! Launching $(TEST_FILE) now !!!\n$(COLOR_NOCOLOR)"
	@./a.out
