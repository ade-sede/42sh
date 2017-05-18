# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ade-sede <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/12 14:34:44 by ade-sede          #+#    #+#              #
#    Updated: 2017/05/18 16:34:05 by ade-sede         ###   ########.fr        #
#    Updated: 2016/12/12 13:30:18 by ade-sede         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

SRC = \
		ft_atoi.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_digit_count.c \
		ft_strrev.c \
		ft_is_upper.c \
		ft_is_lower.c \
		ft_is_space.c \
		ft_strndup.c \
		ft_sort_int_tab.c \
		ft_itoa_base.c \
		ft_power.c \
		ft_strichr.c \
		ft_sqrt.c \
		get_next_line.c \
		ft_buff_wchar.c \
		ft_strmatch.c \
		ft_abs.c \
		ft_buff_wstring.c \
		ft_ishex.c \
		ft_strtrunc.c \
		ft_strnreplace.c \
		ft_atoi_base.c \
		ft_chartostr.c \
		ft_unsigned_itoa_base.c \
		palloc.c \
		printf/conv.c \
	   	printf/conv_fcts.c \
	   	printf/conv_fcts2.c \
	   	printf/field.c \
	   	printf/flags.c \
	   	printf/form.c \
	   	printf/ft_printf.c \
	   	printf/opt.c \
	   	printf/prec.c \
	   	printf/add_flags.c \
	   	printf/conv_types.c \
	   	printf/dprintf.c \
		ft_lst_add.c \
		ft_lst_pushback.c \
		ft_lst_sort_insert.c \
		ft_lst_create.c \
		ft_strchange.c \
		ft_strsurround.c \
		ft_realloc.c \
		fatal.c \
		ft_lst_foreach.c \
		ft_lst_for_n.c \
		ft_lst_del_one.c \
		ft_lst_remove.c \
		ft_lst_get_n.c \
		ft_lst_return_if.c \
		free.c \
		charcmp.c \
		bs_str.c \
		ft_arraydel.c \


SRCDIR = srcs
OBJDIR = objs
INCDIR = includes
CFLAGS = -g -Wall -Wextra -Werror
CC = gcc
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))


all: $(OBJDIR) $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $^ -I$(INCDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/printf

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

test: re
	@$(CC) -g $(TEST_FILE) -I$(INCDIR) -L. -lft
	@echo "Launching LIBFT_TEST now !"
	@./a.out

.PHONY: all clean fclean re
