SRCS=\
main.c \
\
srcs/get_token.c \
srcs/get_token_list.c \
srcs/t_lexer.c \
srcs/t_token.c \
srcs/utils.c \
\
srcs/lexer_action/default.c \
srcs/lexer_action/whitespace.c \
srcs/lexer_action/dquotes.c \
srcs/lexer_action/quotes.c \
srcs/lexer_action/bs.c \
srcs/lexer_action/operator.c \
srcs/lexer_action/newline.c \
srcs/lexer_action/comment.c \
srcs/lexer_action/param_exp.c \
srcs/lexer_action/cmd_subst.c \
srcs/lexer_action/word.c \
\
srcs/id/operator.c \
srcs/id/reserved_words.c

all:
	@rm -rf lexer_test
	@make -C libft
	@gcc -o lexer_test -g $(SRCS) -Iincludes -Ilibft/includes -Llibft -lft -lreadline -D LEXER_DEBUG -fsanitize=address -fno-omit-frame-pointer
