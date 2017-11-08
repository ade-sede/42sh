#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "exec.h"
#include "glob.h"

/*
**
*/

char		**exec_expand(t_token *token)
{
	t_env	*env;
	char	**step_1_ret = NULL;

	/*
	**	Apply param expand, cmd_subst, ar_expand
	*/

	/*
	** Delimiter des tokens d'expansion.
	** Les traiter:
	** - appeler Tilde_expansion, parameter_expansion, command_substitution, and arithmetic_expansion en fonction du token
	** - ces fontions peuvent etre recursive dans le cas de aritmetic_expansion et parameter_expension
	**  ${qweqew-:$lol} ; lol="a\nb"; ->recursif rappele de parameter_expansion
	**  lol -> 1 champs
	**  char *ret "a\nb"
	*/

	/*
	**	Field Split -> n champs
	*/

	/*
	**	Application du globing a CHAQUE CHAMP -> n * glob champs
	*/

	/*
	**	Quote removal de chaque champ.
	*/

	/*
	**	Concatenation dans un char **
	**	ret;
	*/

	/*
	**	
	*/
	if (token->state_info[_T_STATE] == CMD_SUBST)
		step_1_ret = 
}
