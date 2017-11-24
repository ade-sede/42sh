#ifndef EXPAND_H
# define EXPAND_H

# define W_ARRAY_SIZE        10
# define WRDE_SYNTAX		42

# define NO_FIELDSPLITING	0b1
# define NO_GLOBBING	   0b10
# define NO_SHOW_ERROR	   0b100

# define CHAR_IN_SET(c, str) ft_strchr(str, c) != NULL
# include <stdlib.h>
# include "libft.h"

typedef struct	s_expand
{
	char		**av_word;
	char		**av_gword;
	size_t		actlen;
	size_t		maxlen;
	t_word		g_word;
	t_word		word;
	const char	*words;
	size_t		offset;
	const char	*ifs;
	int			flag;
}				t_expand;

int				w_addword (t_expand *exp, t_word *g_word, t_word *word);
int				w_newexp (t_expand *exp);

char			**word_expansion (const char *words, int flag);

int				parse_dquote (t_expand *exp);
int				parse_dollars (t_expand *exp, int quoted);
int				parse_comm (t_expand *exp, int parent_quoted);
int				parse_tilde (t_expand *exp);
int				parse_backtick (t_expand *exp, int quoted);

int				parse_backslash (t_word *g_word, t_word *word, \
		const char *words, size_t *offset);
int				parse_qtd_backslash (t_word *g_word, t_word *word, \
		const char *words, size_t *offet);
int				parse_squote (t_word *g_word, t_word *word, \
		const char *words, size_t *offset);

int				handle_fieldsplitting (char *value, t_expand *exp, int quoted);
int				exec_comm (char *comm, t_expand *exp, int quoted);

int				eval_expr_val (char **expr, long int *result);
int				eval_expr_multdiv (char **expr, long int *result);
int				eval_expr (char *expr, long int *result);
int				parse_arith (t_expand *exp);
int				eval_expr(char *expr, long int *result);
int				eval_expr_multdiv(char **expr, long int *result);
int				eval_expr_val(char **expr, long int *result);
char			*skip_white_space(char *str);
int				parse_param(t_expand *exp, int quoted);
#endif
