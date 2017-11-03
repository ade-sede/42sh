#include "libft.h"
#include "lexer.h"

/*
**	PARAMS:
**		lex is the address of an existing lexer.
**
**	RETVAL:
**		If a token is created, returns the created token.
**		Otherwise (error, nothing to lex) return NULL.
*/

/*
**	Cycle of life :
**	Step 1 = Delimitation automata.
**		- Find the set of possible actions corresponding to the current state.
**		- Within this set, find the exact action corresponding to the given input.
**		- Work is done when we came back to our original state and the last state we poped was complete (has an end defined).
**	Step 2 = Token creation followed by token identification
*/

struct s_lex_action g_lex_action[] = 
{
	{DEFAULT, &lex_action_default},
	{WORD, &lex_action_word}
};

/*
**	Sorry, just wanted to try it once ...
*/

void	(*get_action(ssize_t state))(t_lexer *, ssize_t **)
{
	size_t	i;

	while (g_lex_action[i].state != state)
		++i;
	return (g_lex_action[i].func);
}

/*
**	In the natural flow, every new_value of state_info frees the precent one,
**	and the very last one is kept and used. If unnatural stop occurs, the last
**	value is not used, and must be freed manually.
*/

t_token	*get_token(t_lexer *lex)
{
	/* INIT */
	ssize_t	*state_info;
	t_token	*token;

	token = NULL;
	state_info = NULL;

	/* DELIM */
	while (!(state_info && state_info[_T_END] != -1 && ((ssize_t*)lex->state->data)[_T_STATE] == DEFAULT) && lex->line[lex->pos])
		get_action(((ssize_t*)lex->state->data)[_T_STATE])(lex, &state_info);

	/* Check for errors */
	if (((ssize_t*)lex->state->data)[_T_STATE] == DEFAULT) /* If everything is ok, TOKENIZE */
	{
		//token = create_token();
		//id_token(&token);
	}
	else
		free(state_info);
	return (token);
}
