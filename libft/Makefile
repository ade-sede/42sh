NAME = libft.a
SRC = \
	  ft_abs.c \
	  ft_strlen.c \
	  ft_arraylen.c \
	  palloc.c \
	  ft_putstr.c \
	  ft_putchar.c \
	  ft_bzero.c \
	  ft_memset.c \
	  ft_memalloc.c \
	  ft_calloc.c \
	  ft_memcpy.c \
	  ft_memcmp.c \
	  ft_memccpy.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strichr.c \
	  ft_strncpy.c \
	  ft_strcpy.c \
	  ft_strcmp.c \
	  ft_strncmp.c \
	  ft_strcat.c \
	  ft_strncat.c \
	  ft_strlcat.c \
	  ft_memchr.c \
	  ft_memmove.c \
	  ft_arraydup.c \
	  ft_strdup.c \
	  ft_strstr.c \
	  ft_strnstr.c \
	  ft_atoi.c \
	  ft_is_1.c \
	  ft_is_2.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_memdel.c \
	  ft_strnew.c \
	  ft_strdel.c \
	  ft_strclr.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strequ.c \
	  ft_strnequ.c \
	  ft_strsub.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_strsplit.c \
	  ft_strsplit_quotes.c \
	  ft_strsplit_keep.c \
	  charcmp.c \
	  ft_itoa.c \
	  fatal.c \
	  ft_free.c \
	  ft_buff_wchar.c \
	  ft_lst_add.c \
	  ft_lst_create.c \
	  ft_lst_del_one.c \
	  ft_lst_dup.c \
	  ft_lst_for_n.c \
	  ft_lst_foreach.c \
	  ft_lst_get_n.c \
	  ft_lst_pushback.c \
	  ft_lst_remove.c \
	  ft_lst_return_if.c \
	  ft_lst_sort_insert.c \
	  printf/add_flags.c \
	  printf/conv_fcts.c \
	  printf/conv_types.c \
	  printf/flags.c \
	  printf/ft_printf.c \
	  printf/prec.c \
	  printf/conv.c \
	  printf/conv_fcts2.c \
	  printf/field.c \
	  printf/form.c \
	  printf/opt.c \
	  ft_chartostr.c \
	  ft_strmatch.c \
	  ft_strnreplace.c \
	  ft_strsurround.c \
	  ft_realloc.c \
	  ft_arraydel.c \
	  ft_arraychr.c \
	  ft_strchange.c \
	  ft_putnstr.c \
	  ft_arraymax_f.c \
	  get_next_line.c

OPTI_FLAGS = -O2
SANITIZER =# -fsanitize=address -fno-omit-frame-pointer  && ASAN_OPTIONS=symbolize=1 ASAN_SYMBOLIZER_PATH=/Users/ade-sede/.brew/opt/llvm/bin/llvm-symbolizer
SRCDIR = srcs
OBJDIR = objs
INCDIR = includes
CFLAGS = -g -Wall -Wextra -Werror
CC = clang
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))


all: $(OBJDIR) $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(OPTI_FLAGS) $(CFLAGS) -c -o $@ $^ -I$(INCDIR) $(SANITIZER)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/printf

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

test:	all 
	@$(CC) -g $(TEST_FILE) -I$(INCDIR) -L. -lft
	@echo "Launching LIBFT_TEST now !"
	@./a.out

.PHONY: all clean fclean re
