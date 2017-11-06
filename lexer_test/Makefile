SRCS=\
main.c \
srcs/get_token.c \
srcs/get_token_list.c \
srcs/t_lexer.c \
srcs/t_token.c \
srcs/utils.c \
srcs/lexer_action/default.c \
srcs/lexer_action/whitespace.c \
srcs/lexer_action/word.c

all:
	@make -C libft
	@gcc $(SRCS) -Iincludes -Ilibft/includes -Llibft -lft -lreadline
