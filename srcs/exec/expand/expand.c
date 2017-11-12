#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "exec.h"
#include "glob.h"

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

int		swich_state_quote(char *str, int i)
{
	if (braced_word[end] == '\'' && !is_backslashed(str, i))
		return state == DEFAULT ? QUOTED : DEFAULT;
	if (braced_word[end] == '"' && !is_backslashed(str, i))
		return state == DEFAULT ? DQUOTED : DEFAULT;
	return DEFAULT
}

cmd_subs_action
{
}

int		delim_token(char *str, t_field *field, int start)
{
	t_field_lst	*field = new_field(str);
	t_token_lst	*token = new_token(new_field);

	int	start = 0;
	int	end = 0;
	while (str[end])
	{
		state = swich_state_quote(str, end);
		if (ft_is_on_of(str[end], "$`~"))
		{
			field = create_field(start, end - 1);
			start = end;
		}
		end++;
	}
}
char	**field_splitting()
{
}

void	field_splitting_join(t_token *last_token, char *str)
{
	t_token_lst	*fsplitted_tokens = NULL;

	char **av = field_splitting(new_field->value);

	len = ft_array_len(av);
	if (len == 1)
		return ;
	if (len == 2)
		ft_genlst_add(last_token->last_field, new_field(av[0]));

	if (len >= 3)
	
	fsplitted_tokens = field_splitting(new_field->value);
	first_splitted_field = fsplitted_tokens->value;
	ft_genlst_pushback(token->first_field, fsplitted_tokens->value);
	last_splidded_field = ft_genlst_last(fsplitted_tokens)->value;
}

t_token_lst	*exec_expand_2(char *str)
{
	t_token_lst	*token = new_token(new_field);
	int			start = 0;

	while (str[start] && new_field = delim_token(NULL, start))
	{
		new_field->value = expand(new_field->value);
		if (!new_field->state == DQUOTE && new_field->expand > 0)
		{
		}
	}
}


char		**brace_expand(char *word)
{
	t_token_lst	token_lst = NULL;
	t_expand	expand;

	brace_lst = curly_brackets(word);
	while (brace_lst)
	{
		token_lst = expand();
		ft_genlst_add(&expand->first_token, token_lst);
	}
}
