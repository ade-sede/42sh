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
SRC_FILE = \
	builtin/alias.c \
	builtin/cd.c \
	builtin/echo.c \
	builtin/env.c \
	builtin/exec_builtin.c \
	builtin/exit.c \
	builtin/setenv.c \
	builtin/unalias.c \
	builtin/unsetenv.c \
	\
	completion/comple_bin_matches.c \
	completion/comple_escape.c \
	completion/comple_exit_matched.c \
	completion/comple_file_matches.c \
	completion/comple_glob_matches.c \
	completion/comple_get_input.c \
	completion/comple_get_word_cursor.c \
	completion/comple_init.c \
	completion/comple_matches.c \
	completion/comple_move.c \
	completion/comple_refresh.c \
	completion/comple_signals.c \
	completion/size_term.c \
	completion/ternary_search_tree.c \
	completion/ternary_search_tree_add.c \
	\
	env/add_var.c \
	env/env_create_completion_tree.c \
	env/environ.c \
	env/load_base_env.c \
	env/prompt.c \
	env/prompt_zsh.c \
	env/remove_var.c \
	env/t_env.c \
	\
	exec/exec_bin.c \
	exec/exec_heredoc.c \
	exec/exec_pipe.c \
	exec/exec_redir.c \
	exec/exec_separator.c \
	exec/exec_signals.c \
	exec/exec_simple_commands.c \
	exec/exec_tree.c \
	exec/main_loop.c \
	exec/redir_utils.c \
	\
	globing/curly_bracket_split.c \
	globing/curly_brackets.c \
	globing/curly_brackets_is_range.c \
	globing/curly_brackets_range.c \
	globing/glob.c \
	globing/match.c \
	globing/match_open_dir.c \
	globing/square_bracket.c \
	globing/star.c \
	\
	hash_table/hash.c \
	hash_table/hash_free.c \
	\
	history/btsearch_add.c \
	history/btsearch_del.c \
	history/btsearch_exit.c \
	history/btsearch_get_input.c \
	history/btsearch_init.c \
	history/btsearch_move.c \
	history/btsearch_refresh.c \
	history/btsearch_signals.c \
	history/history_get_input.c \
	history/history_init.c \
	history/history_line_refresh.c \
	history/history_move.c \
	history/history_refresh.c \
	history/load_history.c \
	\
	lexer/expand_alias.c \
	lexer/expand_param.c \
	lexer/expand_tild.c \
	lexer/expand_word.c \
	lexer/lexer.c \
	lexer/match_expand.c \
	lexer/match_operator.c \
	lexer/match_token.c \
	lexer/match_word.c \
	lexer/t_lexer.c \
	lexer/t_token.c \
	\
	line_editing/conf_term.c \
	line_editing/control_d.c \
	line_editing/edit_copy_paste.c \
	line_editing/edit_add.c \
	line_editing/edit_del.c \
	line_editing/edit_exit.c \
	line_editing/edit_init.c \
	line_editing/edit_insert_str.c \
	line_editing/edit_move.c \
	line_editing/edit_move_arrows.c \
	line_editing/edit_move_cursor.c \
	line_editing/edit_refresh.c \
	line_editing/edit_refresh_visu.c \
	line_editing/edit_signals.c \
	line_editing/edit_get_input.c \
	line_editing/put_termcap.c \
	line_editing/edit_get_coor.c \
	line_editing/edit_cursor.c \
	\
	parser/parse.c \
	parser/parse_complex_command.c \
	parser/parse_pipe.c \
	parser/parse_redir.c \
	parser/parse_simple_command.c \
	parser/t_ast.c \
	parser/t_pipe.c \
	\
	failure/get_errno_1.c \
	failure/get_errno_2.c \
	failure/get_errno_3.c \
	failure/return_failure.c \
	\
	main.c

INCLUDES_FILES = \
	ast.h \
	builtin.h \
	completion.h \
	env.h \
	exec.h \
	glob.h \
	glob_struct.h \
	hash_table.h \
	history.h \
	lexer.h \
	line_editing.h \
	t_line.h \
	parser.h \
	pipe.h \
	t_lexer.h \
	token.h

NAME ?= 21sh

# defining those variables allows auto completion to occure.
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

.phony: all test hello_word lib $(OBJ_DIR) $(NAME) clean fclean re

all: hello_word lib $(OBJ_DIR) $(NAME) $(INCLUDES_DEP)
	@printf "$(COLOR_CLEAR)$(COLOR_GREEN)successfully created $(COLOR_BLUE)$(NAME) !!!$(COLOR_NOCOLOR)\n"

hello_word:
	@printf "$(COLOR_VIOLET)$(COLOR_UNDERLINE)compiling$(COLOR_NOCOLOR) $(COLOR_BLUE)$(NAME) ...$(COLOR_NOCOLOR)\n"

lib:
	@make -C $(LIB_DIR) APPEND="$(APPEND)" OPTIMIZATION="$(OPTIMIZATION)" CC="$(CC)"

$(NAME): $(OBJS) 
	@printf "$(COLOR_GREEN)successfully created objects files for binary $(COLOR_BLUE)$(NAME) !!!$(COLOR_NOCOLOR)\n"
	@printf "$(COLOR_VIOLET)creating $(NAME) ... $(COLOR_NOCOLOR)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(INCLUDES) $(SANITIZER) $(APPEND) $(OPTIMIZATION)
	@printf "$(COLOR_UP)$(COLOR_CLEAR)"
	
$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)
	@/bin/mkdir -p $(OBJ_DIR)/builtin
	@/bin/mkdir -p $(OBJ_DIR)/completion
	@/bin/mkdir -p $(OBJ_DIR)/env
	@/bin/mkdir -p $(OBJ_DIR)/exec
	@/bin/mkdir -p $(OBJ_DIR)/globing
	@/bin/mkdir -p $(OBJ_DIR)/hash_table
	@/bin/mkdir -p $(OBJ_DIR)/history
	@/bin/mkdir -p $(OBJ_DIR)/lexer
	@/bin/mkdir -p $(OBJ_DIR)/line_editing
	@/bin/mkdir -p $(OBJ_DIR)/main.c
	@/bin/mkdir -p $(OBJ_DIR)/parser
	@/bin/mkdir -p $(OBJ_DIR)/failure

clean:
	@make -C $(LIB_DIR) clean
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean
	@/bin/rm -f $(NAME)

re: fclean all

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@printf "$(COLOR_VIOLET)creating objects files for library $(COLOR_BLUE)$(NAME) ... \n$(COLOR_CYAN)"
	$(CC) $(OPTIMIZATION) $(CFLAGS) $(INCLUDES) $(SANITIZER) $(APPEND) -c -o $@ $^
	@printf "\n$(COLOR_NOCOLOR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)"

test: all 
	@printf "$(COLOR_VIOLET)compiling test $(TEST_FILE) ... $(COLOR_RESET)\n"
	@$(CC) -g $(TEST_FILE) $(INCLUDES) $(LDFLAGS) $(SANITIZER) $(APPEND)
	@printf "$(COLOR_GREEN)done !!! launching $(TEST_FILE) now !!!\n$(COLOR_NOCOLOR)"
	@./a.out
