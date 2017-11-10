#include "exec.h"
#include "local.h"

/*
**	wordlist         : wordlist WORD
**	                 |          WORD
*/
		
int		exec_wordlist(t_ast *wordlist, char *var, t_ast *do_group)
{
	char	*word;

	word = wordlist->child[1] ? ft_strdup(wordlist->child[1]->token->value) :
		 ft_strdup(wordlist->child[0]->token->value);
	if (!wordlist)
		return (EXIT_SUCCESS);
	add_to_local(&singleton_env()->local, ft_strjoin3_free(var, "=", word, 0b1));
	exec(do_group);
	if (is_symb(wordlist->child[0], WORDLIST))
		return (exec_wordlist(wordlist->child[0], var, do_group));
	return (EXIT_SUCCESS);
}

/*
**	for_clause       : For name                                      do_group
**	                 | For name                       sequential_sep do_group
**	                 | For name linebreak in          sequential_sep do_group
**	                 | For name linebreak in wordlist sequential_sep do_group
*/

int exec_for_clause(t_ast *ast)
{

	debug_symbol(ast->child[1]);
	if (ast->child[6])
		return (exec_wordlist(ast->child[4], ast->child[1]->child[0]->token->value, ast->child[6]));
	return (EXIT_SUCCESS);
}
