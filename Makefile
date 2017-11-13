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
	builtin/unset.c \
	builtin/set.c \
	builtin/fg.c \
	builtin/bg.c \
	builtin/jobs.c \
	builtin/function_set.c \
	builtin/read.c \
	builtin/read_options.c \
	builtin/history.c \
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
	env/local_add.c \
	env/env_add.c \
	env/env_create_completion_tree.c \
	env/environ.c \
	env/load_base_env.c \
	env/local_get.c \
	env/prompt.c \
	env/prompt_zsh.c \
	env/env_remove.c \
	env/local_remove.c \
	env/t_env.c \
	env/get_ps1.c \
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
	history/history_write.c \
	history/load_history.c \
	\
	lexer/get_token.c \
	lexer/get_token_list.c \
	lexer/t_lexer.c \
	lexer/t_token.c \
	lexer/utils.c \
	lexer/lexer_construct_prompt.c \
\
	lexer/id/get_token_id.c \
	lexer/id/operator.c \
	lexer/id/reserved_words.c \
	lexer/id/words.c \
\
	lexer/lexer_action/bs.c \
	lexer/lexer_action/cmd_subst.c \
	lexer/lexer_action/comment.c \
	lexer/lexer_action/default.c \
	lexer/lexer_action/dquotes.c \
	lexer/lexer_action/newline.c \
	lexer/lexer_action/operator.c \
	lexer/lexer_action/param_exp.c \
	lexer/lexer_action/quotes.c \
	lexer/lexer_action/whitespace.c \
	lexer/lexer_action/word.c \
	\
	line_editing/conf_term.c \
	line_editing/edit_reopen.c \
	line_editing/edit_write.c \
	line_editing/edit_control_d.c \
	line_editing/edit_control_l.c \
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
	line_editing/edit_signals.c \
	line_editing/edit_get_input.c \
	line_editing/put_termcap.c \
	line_editing/edit_get_coor.c \
	line_editing/edit_cursor.c \
	\
	parser/get_action.c \
	parser/parser.c \
	parser/parser_construct_prompt.c \
	parser/utils.c \
	\
	failure/get_errno_1.c \
	failure/get_errno_2.c \
	failure/get_errno_3.c \
	failure/return_failure.c \
	\
	signal/all_signal_dfl.c \
	signal/all_signal_ign.c \
	\
	exec/exec_redir.c \
	exec/lex_and_parse.c \
	exec/main_loop.c \
	exec/redir_utils.c \
	exec/exec_utils.c \
	exec/exec_io_redirect.c \
	exec/exec_redirect_list.c \
	exec/exec_bin.c \
	 \
	exec/symbol/exec.c \
	exec/symbol/exec_and_or.c \
	exec/symbol/exec_brace_group.c \
	exec/symbol/exec_case_clause.c \
	exec/symbol/exec_command.c \
	exec/symbol/exec_complete_command.c \
	exec/symbol/exec_complete_commands.c \
	exec/symbol/exec_compound_command.c \
	exec/symbol/exec_compound_list.c \
	exec/symbol/exec_do_group.c \
	exec/symbol/exec_else_part.c \
	exec/symbol/exec_for_clause.c \
	exec/symbol/exec_function_body.c \
	exec/symbol/exec_function_definition.c \
	exec/symbol/exec_if_clause.c \
	exec/symbol/exec_pipe_sequence.c \
	exec/symbol/exec_pipeline.c \
	exec/symbol/exec_program.c \
	exec/symbol/exec_simple_command.c \
	exec/symbol/exec_subshell.c \
	exec/symbol/exec_term.c \
	exec/symbol/exec_until_clause.c \
	exec/symbol/exec_while_clause.c \
	exec/debug_symbol.c \
	exec/debug_token.c \
	exec/exec_function.c \
	\
	job_control/job_background.c \
	job_control/job_continue.c \
	job_control/job_foreground.c \
	job_control/job_init.c \
	job_control/job_launch.c \
	job_control/job_notification.c \
	job_control/job_utils.c \
	job_control/singleton_jc.c \
	job_control/job_format.c \
	job_control/job_mark_status.c \
	job_control/job_wait.c \
	job_control/job_fill_process_av.c \
	\
	main.c \

INCLUDES_FILES = \
	t_ast.h \
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
	t_token.h \
	local.h \
	my_signal.h \
	job_control.h \
	parser.h \

NAME ?= 42sh

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
CFLAGS ?= -g3 -Wall -Wextra -Werror
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
	
$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)
	@/bin/mkdir -p $(OBJ_DIR)/builtin
	@/bin/mkdir -p $(OBJ_DIR)/completion
	@/bin/mkdir -p $(OBJ_DIR)/env
	@/bin/mkdir -p $(OBJ_DIR)/exec
	@/bin/mkdir -p $(OBJ_DIR)/exec/symbol/
	@/bin/mkdir -p $(OBJ_DIR)/exec/expand/
	@/bin/mkdir -p $(OBJ_DIR)/globing
	@/bin/mkdir -p $(OBJ_DIR)/hash_table
	@/bin/mkdir -p $(OBJ_DIR)/history
	@/bin/mkdir -p $(OBJ_DIR)/lexer
	@/bin/mkdir -p $(OBJ_DIR)/lexer/id/
	@/bin/mkdir -p $(OBJ_DIR)/lexer/lexer_action/
	@/bin/mkdir -p $(OBJ_DIR)/line_editing
	@/bin/mkdir -p $(OBJ_DIR)/parser
	@/bin/mkdir -p $(OBJ_DIR)/failure
	@/bin/mkdir -p $(OBJ_DIR)/signal
	@/bin/mkdir -p $(OBJ_DIR)/job_control

clean:
	@make -C $(LIB_DIR) clean
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean
	@/bin/rm -f $(NAME)

re: fclean
	make

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@printf "$(COLOR_VIOLET)creating objects files for library $(COLOR_BLUE)$(NAME) ... \n$(COLOR_CYAN)"
	$(CC) $(OPTIMIZATION) $(CFLAGS) $(INCLUDES) $(SANITIZER) $(APPEND) -c -o $@ $^
	@printf "\n$(COLOR_NOCOLOR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)"

test: all 
	@printf "$(COLOR_VIOLET)compiling test $(TEST_FILE) ... $(COLOR_RESET)\n"
	@$(CC) -g $(TEST_FILE) $(INCLUDES) $(LDFLAGS) $(SANITIZER) $(APPEND)
	@printf "$(COLOR_GREEN)done !!! launching $(TEST_FILE) now !!!\n$(COLOR_NOCOLOR)"
	@./a.out
