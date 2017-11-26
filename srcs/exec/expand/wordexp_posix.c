/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordexp_posix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:04 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "environ.h"
#include "exec.h"
#include "local.h"
#include "glob.h"
#include "expand.h"

static char		**list_to_array(t_list *lst)
{
	size_t		n;
	char		**res;
	int			i;

	n = ft_lst_len(lst);
	res = ft_memalloc(sizeof(char *) * (n + 1));
	i = 0;
	while (lst)
	{
		res[i] = (char *)lst->data;
		lst = lst->next;
		i++;
	}
	return (res);
}

static char		**pathname_expension(t_expand *ex)
{
	t_list		*ml;
	size_t		i;
	char		*no_match[2];
	char		**av;

	av = ft_memalloc(sizeof(char *) * (1));
	no_match[1] = NULL;
	i = -1;
	while (++i < ex->actlen)
		if ((ml = (has_glob_char(ex->av_gword[i])) ? glob(ex->av_gword[i]) : 0))
		{
			av = ft_arrayjoin_free(av, list_to_array(ml), 0b11);
			ft_simple_lst_remove(&ml, NULL);
			ft_strdel(&ex->av_word[i]);
			ft_strdel(&ex->av_gword[i]);
		}
		else
		{
			no_match[0] = ex->av_word[i];
			av = ft_arrayjoin_free(av, no_match, 0b10);
			ft_strdel(&ex->av_gword[i]);
		}
	free(ex->av_gword);
	free(ex->av_word);
	return (av);
}

static char		**brace_expension(const char *words)
{
	t_list		*match_list;
	char		**matches;

	match_list = expand_curly_brackets((char *)words);
	if (match_list)
	{
		matches = list_to_array(match_list);
		ft_simple_lst_remove(&match_list, NULL);
	}
	else
	{
		matches = ft_memalloc(sizeof(char *) * (2));
		matches[0] = ft_strdup(words);
	}
	return (matches);
}

static void		parse_loop(const char *words, t_expand *exp)
{
	w_newword(&exp->word);
	w_newword(&exp->g_word);
	exp->offset = -1;
	exp->words = words;
	while (words[++exp->offset])
		if (words[exp->offset] == '\\')
			parse_backslash(&exp->g_word, &exp->word, words, &exp->offset);
		else if (words[exp->offset] == '"' && ++exp->offset)
			parse_dquote(exp);
		else if (words[exp->offset] == '\'' && ++exp->offset)
			parse_squote(&exp->g_word, &exp->word, words, &exp->offset);
		else if (words[exp->offset] == '`')
			parse_backtick(exp, 0);
		else if (words[exp->offset] == '$')
			parse_dollars(exp, 0);
		else if (words[exp->offset] == '~')
			parse_tilde(exp);
		else
		{
			w_addchar(&exp->word, words[exp->offset]);
			w_addchar(&exp->g_word, words[exp->offset]);
		}
	if (exp->word.str != NULL)
		w_addword(exp, &exp->g_word, &exp->word);
}

char			**word_expansion(const char *words, int flag)
{
	char		**braced_words;
	t_expand	exp;
	size_t		i;

	(void)flag;
	w_newexp(&exp);
	exp.flag = flag;
	exp.ifs = ft_strdup(var_get_value(singleton_env(), "IFS"));
	if (exp.ifs == NULL)
		exp.ifs = ft_strdup(" \t\n");
	braced_words = brace_expension(words);
	i = 0;
	while (braced_words[i])
	{
		parse_loop(braced_words[i], &exp);
		i++;
	}
	free((void *)exp.ifs);
	ft_arraydel(&braced_words);
	if (!(flag & NO_GLOBBING))
		return (pathname_expension(&exp));
	ft_arraydel(&exp.av_gword);
	return (exp.av_word);
}
