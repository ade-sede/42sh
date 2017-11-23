#include "exec.h"
#include <stdio.h>
#include "local.h"
#include "expand.h"

/*
**	wordlist         : wordlist WORD
**	                 |          WORD
*/

char	**expand_wordlist(t_ast *wordlist, char **array_word)
{
	char		*word;
	char		**word_expanded;

	word = wordlist->child[1] ? wordlist->child[1]->token->value :
			wordlist->child[0]->token->value;
	word_expanded = word_expansion(word, 0);
	array_word = array_word ?
		ft_arrayjoin_free(array_word, word_expanded, 0b11) : word_expanded;
	if (is_symb(wordlist->child[0], WORDLIST))
		return (expand_wordlist(wordlist->child[0], array_word));
	return (array_word);
}

/*
**	for_clause       : For name                                      do_group
**	                 | For name                       sequential_sep do_group
**	                 | For name linebreak in          sequential_sep do_group
**	                 | For name linebreak in wordlist sequential_sep do_group
*/

int		exec_for_clause(t_ast *ast)
{
	char		**array_word;
	int			i;
	t_ast		*do_group;
	char		*var;

	if (ast->child[4] && is_symb(ast->child[4], WORDLIST))
		array_word = expand_wordlist(ast->child[4], NULL);
	else
		return (EXIT_SUCCESS);
	do_group = ast->child[6];
	var = ast->child[1]->child[0]->token->value;
	i = 0;
	while (array_word[i])
	{
		local_add_change_from_key_value(singleton_env(), var, array_word[i]);
		exec(do_group);
		++i;
	}
	return (EXIT_SUCCESS);
}
