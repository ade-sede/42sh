#ifndef STRING_H
# define STRING_H

#include "libft.h"
#define W_BUFF_SIZE        30

typedef struct	s_word
{
	char		*str;
	size_t		actlen;
	size_t		maxlen;
}				t_word;

void	w_newword (t_word *word);
char	*w_addchar (t_word *word, const char ch);
char	*w_addmem (t_word *word, const char *str, size_t len);
char	*w_addstr (t_word *word, const char *str);
char	*w_insertchar(t_word *word, const char ch, size_t index);
char	*w_insertstr(t_word *word, const char *str, size_t index);
void	w_free (t_word *word);
#endif
