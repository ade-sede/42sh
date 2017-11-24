

SRCS=\
main.c\
srcs/bang_expand.c\
srcs/word_designator_expand.c\
srcs/modifier_expand.c\
srcs/event_expand.c

all:
	gcc -o test $(SRCS) -lft -Llibft -Ilibft/includes -Iincludes -lreadline
	# gcc -o test $(SRCS) -lft -Llibft -Ilibft/includes -Iincludes -lreadline -fsanitize=address -fno-omit-frame-pointer
