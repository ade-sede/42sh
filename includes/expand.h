#ifndef EXPAND_H
# define EXPAND_H

#define W_BUFF_SIZE        10
#define W_ARRAY_SIZE        10
#define WRDE_SYNTAX		42

#define NO_FIELDSPLITING	0b1
#define NO_GLOBBING	   0b10

#define CHAR_IN_SET(c, str) ft_strchr(str, c) != NULL
#include <stdlib.h>

typedef struct	s_expand
{
	char		**av_word;
	char		**av_gword;
	size_t		actlen;
	size_t		maxlen;
}				t_expand;

typedef struct	s_word
{
	char		*str;
	size_t		actlen;
	size_t		maxlen;
}				t_word;

void	w_newword (t_word *word);
void	*ft_realloc_2(void *mem, size_t old_size, size_t new_size);
char	*w_addchar (t_word *word, char ch);
char	*w_addmem (t_word *word, const char *str, size_t len);
char	*w_addstr (t_word *word, const char *str);
int		w_addword (t_expand *exp, t_word *g_word, t_word *word);
int		w_newexp (t_expand *exp);
void	w_free (t_word *word);

char	**word_expansion (const char *words, int flag);
int		parse_dquote (t_word *g_word, t_word *word,
		const char *words, size_t *offset,
		t_expand *exp, const char *ifs);
int		parse_squote (t_word *g_word, t_word *word, const char *words, size_t *offset);
int		parse_backslash (t_word *g_word, t_word *word, const char *words, size_t *offset);
int		parse_qtd_backslash (t_word *g_word, t_word *word, const char *words, size_t *offset);
int		parse_dollars (t_word *g_word, t_word *word,
		const char *words, size_t *offset,
		t_expand *exp, const char *ifs,
		int quoted);
int		parse_comm (t_word *g_word, t_word *word,
		const char *words, size_t *offset,
		t_expand *exp, const char *ifs,
		int quoted);

int parse_tilde (t_word *g_word, t_word *word,
             const char *words, size_t *offset);

int		parse_backtick (t_word *g_word, t_word *word,
		const char *words, size_t *offset,
		t_expand *exp, const char *ifs,
		int quoted);
int		handle_fieldsplitting (char *value, t_word *g_word, t_word *word,
		t_expand *exp, const char *ifs, int quoted);
int		exec_comm (char *comm, t_word *g_word,t_word *word,
		t_expand *exp, const char *ifs, int quoted);
#endif
