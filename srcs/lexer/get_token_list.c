#include"lexer.h"
#include "libft.h"

#ifdef LEXER_DEBUG
#include <stdio.h>
static struct s_debug_token_state g_debug_token_state[]=
{
	{DEFAULT,"DEFAULT"},
	{WORD,"WORD"},
	{WHITESPACE,"WHITESPACE"},
	{COMMENT,"COMMENT"},
	{OPERATOR,"OPERATOR"},
	{PARAM_EXP,"PARAM_EXP"},
	{CMD_SUBST,"CMD_SUBST"},
	{TILD_EXP,"TILD_EXP"},
	{AR_EXP,"AR_EXP"},
	{DQUOTES,"DQUOTES"},
	{QUOTES,"QUOTES"},
	{BS,"BS"},
	{NEWLINE, "NEWLINE"},
	{-1, NULL}
};

static struct s_debug_token_id g_debug_token_id[] =
{
	{TK_WORD, "TK_WORD"  },
	{TK_ASSIGNMENT_WORD, "TK_ASSIGNMENT_WORD" },
	{TK_NAME, "TK_NAME" },
	{TK_NEWLINE, "TK_NEWLINE" },
	{TK_IO_NUMBER, "TK_IO_NUMBER" },
	{TK_LESS, "TK_LESS" },
	{TK_HERE, "TK_HERE" },
	{TK_GREAT, "TK_GREAT" },
	{TK_SEMI, "TK_SEMI" },
	{TK_PIPE, "TK_PIPE" },
	{TK_AND, "TK_AND" },
	{TK_AND_IF, "TK_AND_IF" },
	{TK_OR_IF, "TK_OR_IF" },
	{TK_DSEMI, "TK_DSEMI" },
	{TK_DLESS, "TK_DLESS" },
	{TK_DGREAT, "TK_DGREAT" },
	{TK_LESSAND, "TK_LESSAND" },
	{TK_GREATAND, "TK_GREATAND" },
	{TK_LESSGREAT, "TK_LESSGREAT" },
	{TK_DLESSDASH, "TK_DLESSDASH" },
	{TK_CLOBBER, "TK_CLOBBER" },
	{TK_IF, "TK_IF" },
	{TK_THEN, "TK_THEN" },
	{TK_ELSE, "TK_ELSE" },
	{TK_ELIF, "TK_ELIF" },
	{TK_FI, "TK_FI" },
	{TK_DO, "TK_DO" },
	{TK_DONE, "TK_DONE" },
	{TK_CASE, "TK_CASE" },
	{TK_ESAC, "TK_ESAC" },
	{TK_WHILE, "TK_WHILE" },
	{TK_UNTIL, "TK_UNTIL" },
	{TK_FOR, "TK_FOR" },
	{TK_LBRACE, "TK_LBRACE" },
	{TK_RBRACE, "TK_RBRACE" },
	{TK_BANG, "TK_BANG" },
	{TK_LPAREN, "TK_LPAREN" },
	{TK_RPAREN, "TK_RPAREN" },
	{TK_IN, "TK_IN" },
	{$, "$"},
	{-1, NULL}
};

static char	*get_state(int state)
{
	int	i = 0;

	while  (g_debug_token_state[i].state != state)
		++i;
	return (g_debug_token_state[i].name);
}

static char	*get_id(int id)
{
	int	i = 0;

	while  (g_debug_token_id[i].id != id)
		++i;
	return (g_debug_token_id[i].name);
}

static int	get_debug_tab_info(t_list *token_list, size_t *nb, size_t *value_size, size_t *state_size, size_t *id_size)
{
	t_token	*token = NULL;
	size_t	token_value_size = 0;
	size_t	token_id_size = 0;
	size_t	token_state_size = 0;

	while (token_list)
	{
		token = token_list->data;

		/* Value_size */
		token_value_size = ft_strlen(token->value);
		if (token_value_size > *value_size)
			*value_size = token_value_size;

		/* State_size */
		token_state_size = ft_strlen(get_state(token->state_info->state));
		if (token_state_size > *state_size)
			*state_size = token_state_size;

		/*  Id size */
		token_id_size = ft_strlen(get_id(token->id));
		if (token_id_size > *id_size)
			*id_size = token_id_size;


		/* NUMBER */
		(*nb)++;

		/* GO NEXT */
		token_list = token_list->next;
	}
	return (1);
}

static	int	debug_token_list(t_list *token_list)
{
	t_token	*token;
	size_t	value_size = 0;
	size_t	id_size = 0;
	size_t	state_size = 0;
	size_t	nb = 0;
	int		i = 1;

	get_debug_tab_info(token_list, &nb, &value_size, &state_size, &id_size);
	while (token_list)
	{
		token = token_list->data;
		/* Print bar */
		printf("%s", i == 1 ? "\u250c" : "\u251c");
		for (size_t i = 0; i != value_size + 2; i++)
			printf("%s", "\u2500");
		printf("%s", i == 1 ? "\u252c" : "\u253c");
		for (size_t i = 0; i != id_size + 2; i++)
			printf("%s", "\u2500");
		printf("%s", i == 1 ? "\u252c" : "\u253c");
		for (size_t i = 0; i != state_size + 2; i++)
			printf("%s", "\u2500");
		printf("%s", i == 1 ? "\u2510" : "\u2524");
		printf("\n");


		/* Print token */

		printf("%s", "\u2502");
		printf(" %s", token->value);
		for (int i = value_size - ft_strlen(token->value) + 1; i; --i)
			printf(" ");
		printf("%s", "\u2502");
		printf(" %s", get_id(token->id));
		for (int i = id_size - ft_strlen(get_id(token->id)) + 1; i; --i)
			printf(" ");
		printf("%s", "\u2502");
		printf(" %s", get_state(token->state_info->state));
		for (int i = state_size - ft_strlen(get_state(token->state_info->state)) + 1; i; --i)
			printf(" ");
		printf("%s", "\u2502");
		printf("\n");

		i++;
		token_list = token_list->next;
	}
	/* Print bot line */
	printf("%s", "\u2514");
	for (size_t i = 0; i != value_size + 2; i++)
		printf("%s", "\u2500");
	printf("%s", "\u2534");
	for (size_t i = 0; i != id_size + 2; i++)
		printf("%s", "\u2500");
	printf("%s", "\u2534");
	for (size_t i = 0; i != state_size + 2; i++)
		printf("%s", "\u2500");
	printf("%s\n", "\u2518");
	return (1);
}
#endif
/*
**	PARAMS:
**		lex is the address of an already existing lexer.
**		token_list is the address of a t_list, where all generated tokens must be
**		stored in the right order (reading order).
**		alias_list is the list of valid alias used to expand command words.
**	
**	LOCAL VARIABLES:
**		token is used to received the token from get_token();
**		node is a t_list node that will be appended to token_list. It either
**		the node containing the generated token, or the list of token generated
**		after alias expansion.
**	
**	RETURN_VALUE:
**		Returns the state at the top of the lexer's state stack at the end of the function.
**		Upon successful completion, this state shall be DEFAULT. Otherwise,
**		this state will be used to handle error appropriately (reopen prompt /
**		abort command).
*/

/*
**	This function's job is concatening a list of tokens (returned one by one by
**	the get_token() function), and concatenate them in a list of tokens, after
**	applying alias expansion or history expansion if necessary.  As for each alias expansion and history expansion many
**	tokens can be generated, and alias_expansion being recursive, this function
**	will be called again within alias expansion and history expansion.
**	If history expansion is done, lex->line must be edited, and the placeholder
**	replaced by its expanded value. Must apply the offset (value_size -
**	place_holder_size) to lex->pos before resuming lexing.
*/

/*
**	Comments and whitespaces are delimited too for syntax coloring purposes,
**	but the parser has no uses for them, so they should be discarded here.
*/


#include <stdio.h>
int		get_token_list(t_lexer *lex, t_list **token_list, t_list *alias_list)
{
	t_token	*token;
	t_list	*node;
	t_list	*reversed_node;

	while (lex->line[lex->pos] && (token = get_token(lex)) != NULL)
	{
#ifdef LEXER_DEBUG
		dprintf(2, "CLOSED A TOKEN\n");
#endif
		/* If token is a whitespace or a comment, discard it. Otherwise proceed to concatenation */

		/* If token is a cmd_name, alias expand it. */
		if (token->state_info->state == COMMENT || token->state_info->state == WHITESPACE)
			free_token(token);
		else
		{
			if (!(node = expand_alias(lex, token, alias_list)))
			{
				node = ft_simple_lst_create(token);
				reversed_node = ft_simple_lst_create(token);
				ft_simple_lst_add(&lex->reversed_list, reversed_node);
			}
			ft_simple_lst_pushback(token_list, node);
		}
	}
#ifdef LEXER_DEBUG
	debug_token_list(*token_list);
#endif
	return ((((struct s_info*)lex->state->data)->state != DEFAULT) ? LEXER_REOPEN : LEXER_SUCCESS);
}
