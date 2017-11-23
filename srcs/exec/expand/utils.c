#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

int		w_addword(t_expand *exp, t_word *g_word, t_word *word)
{
	int		allocated;

	if (exp->actlen == exp->maxlen)
	{
		exp->maxlen += W_ARRAY_SIZE;
		exp->av_word =(char **)cl_realloc(sizeof(char *) * exp->actlen,
				exp->av_word, sizeof(char *) *(1 + exp->maxlen));
		exp->av_gword =(char **)cl_realloc(sizeof(char *) * exp->actlen,
				exp->av_gword, sizeof(char *) *(1 + exp->maxlen));
	}
	allocated = 0;
	if (g_word->str == NULL)
		g_word->str = ft_strdup("");
	if (word->str == NULL)
		word->str = ft_strdup("");
	exp->av_word[exp->actlen] = word->str;
	exp->av_gword[exp->actlen] = g_word->str;
	exp->actlen += + 1;
	w_newword(word);
	w_newword(g_word);
	return (1);
}

int		w_newexp(t_expand *exp)
{
	ft_bzero(exp, sizeof(t_expand));
	exp->av_word =(char **)ft_memalloc(sizeof(char *) * 1);
	exp->av_gword =(char **)ft_memalloc(sizeof(char *) * 1);
	exp->actlen = 0;
	exp->maxlen = 0;
	return (1);
}
