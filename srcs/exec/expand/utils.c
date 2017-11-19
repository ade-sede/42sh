#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

/*
**	void	w_newword (t_word *word) {
**		word->str = NULL;
**		word->actlen = 0;
**		word->maxlen = 0;
**	}
**	
**	void	w_free (t_word *word)
**	{
**		ft_strdel(&word->str);
**		word->actlen = 0;
**		word->maxlen = 0;
**	}
**	
**	void	*ft_realloc_2(void *mem, size_t old_size, size_t new_size)
**	{
**		void	*new_mem;
**	
**		new_mem = ft_memalloc(new_size);
**		if (mem)
**		{
**			ft_memcpy(new_mem, mem, old_size);
**			free(mem);
**		}
**		return (new_mem);
**	}
**	
**	char	*w_addchar (t_word *word, char ch)
**	{
**		if (word->actlen == word->maxlen)
**		{
**			word->maxlen += W_BUFF_SIZE;
**			word->str = (char *)ft_realloc_2 (word->str, word->actlen, 1 + word->maxlen);
**		}
**		word->str[word->actlen] = ch;
**		word->actlen++;
**		return (word->str);
**	}
**	
**	char	*w_addmem (t_word *word, const char *str, size_t len)
**	{
**		if (word->actlen + len > word->maxlen)
**		{
**			word->maxlen += MAX (2 * len, W_BUFF_SIZE);
**			word->str = (char *)ft_realloc_2 (word->str, word->actlen, 1 + word->maxlen);
**		}
**		ft_memcpy(&word->str[word->actlen], str, len);
**		word->actlen += len;
**		return (word->str);
**	}
**	
**	char	*w_addstr (t_word *word, const char *str)
**	{
**		size_t len;
**	
**		len = ft_strlen (str);
**		return (w_addmem(word, str, len));
**	}
*/

int		w_addword (t_expand *exp, t_word *g_word, t_word *word)
{
	int		allocated;


#ifdef EXPAND_DEBUG
	fprintf(stderr,"BEGIN W_ADDWORD : exp->actlen: {%zu} exp->maxlen: {%zu}\n", exp->actlen, exp->maxlen);
 #endif
	if (exp->actlen == exp->maxlen)
	{
		exp->maxlen += W_ARRAY_SIZE;
		exp->av_word = (char **)ft_realloc(sizeof(char *) * exp->actlen, exp->av_word,  sizeof(char *) * (1 + exp->maxlen));
		exp->av_gword = (char **)ft_realloc(sizeof(char *) * exp->actlen, exp->av_gword, sizeof(char *) *  (1 + exp->maxlen));
	}
	allocated = 0;
	if (g_word->str == NULL)
		g_word->str = ft_strdup ("");
	if (word->str == NULL)
		word->str = ft_strdup ("");
	exp->av_word[exp->actlen] = word->str;
	exp->av_gword[exp->actlen] = g_word->str;
	exp->actlen += + 1;
	w_newword (word);
	w_newword (g_word);
#ifdef EXPAND_DEBUG
	fprintf(stderr,"end W_ADDWORD : exp->actlen: {%zu} exp->maxlen: {%zu}\n", exp->actlen, exp->maxlen);
 #endif
	return (1);
}

int		w_newexp (t_expand *exp)
{
	ft_bzero(exp, sizeof(t_expand));
	exp->av_word = (char **)ft_memalloc(sizeof(char *) * 1);
	exp->av_gword = (char **)ft_memalloc(sizeof(char *) * 1);
	exp->actlen = 0;
	exp->maxlen = 0;
	return (1);
}
