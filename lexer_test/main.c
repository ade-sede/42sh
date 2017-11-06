#include "libft.h"
#include "lexer.h"
#include "t_lexer.h"
#include <stdio.h>
#include <readline/readline.h>

struct s_debug_token_id
{
	int		id;
	char	*name;
};

struct s_debug_token_state
{
	int		state;
	char	*name;
};

struct s_debug_token_state g_debug_token_state[]=
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
	{HIST_EXP,"HIST_EXP"},
	{-1, NULL}
};

struct s_debug_token_id g_debug_token_id[] =
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

	while  (g_debug_token_state->state != state && g_debug_token_state->state != -1)
		++i;
	return (g_debug_token_state->name);
}

static char	*get_id(int id)
{
	int	i = 0;
	while  (g_debug_token_id->id != id && g_debug_token_id->id != -1)
		++i;
	return (g_debug_token_id->name);
}

static int	get_debug_tab_info(t_list *token_list, size_t *nb, size_t *value_size, size_t *state_size, size_t *id_size, size_t *end_size, size_t *start_size)
{
	t_token	*token = NULL;
	char	*itoa_end = NULL;
	char	*itoa_start = NULL;
	size_t	token_value_size = 0;
	size_t	token_id_size = 0;
	size_t	token_state_size = 0;
	size_t	token_start_size = 0;
	size_t	token_end_size = 0;

	while (token_list)
	{
		token = token_list->data;

		/* Value_size */
		token_value_size = ft_strlen(token->value);
		if (token_value_size > *value_size)
			*value_size = token_value_size;

		/* State_size */
		token_state_size = ft_strlen(get_state(token->state_info[_T_STATE]));
		if (token_state_size > *state_size)
			*state_size = token_state_size;

		/*  Id size */
		token_id_size = ft_strlen(get_id(token->state_info[_T_STATE]));
		if (token_id_size > *id_size)
			*id_size = token_id_size;

		/* end */
		itoa_end = ft_itoa_base(token->state_info[_T_END], 10);
		token_end_size = ft_strlen(itoa_end);
		free(itoa_end);
		if (token_end_size > *end_size)
			*end_size = token_end_size;

		/* state */
		itoa_start = ft_itoa_base(token->state_info[_T_START], 10);
		token_start_size = ft_strlen(itoa_start);
		free(itoa_start);
		if (token_start_size > *start_size)
			*start_size = token_start_size;




		/* NUMBER */
		(*nb)++;

		/* GO NEXT */
		token_list = token_list->next;
	}
	return (1);
}

static	int	debug_token_list(t_list *token_list)
{
	size_t	value_size = 0;
	size_t	id_size = 0;
	size_t	state_size = 0;
	size_t	start_size = 0;
	size_t	end_size = 0;
	size_t	nb = 0;
	int		i = 1;

	get_debug_tab_info(token_list, &nb, &value_size, &state_size, &id_size, &end_size, &start_size);
	while (token_list)
	{
		/* Print bar */
		printf("%s", i == 1 ? "\u250c" : "\u252c");
		for (size_t i; i != value_size + 2; i++)
			printf("%s", "\u2500");
		printf("%s", i == 1 ? "\u252c" : "\u253c");
		for (size_t i; i != id_size + 2; i++)
			printf("%s", "\u2500");
		printf("%s", i == 1 ? "\u252c" : "\u253c");
		for (size_t i; i != start_size + 2; i++)
			printf("%s", "\u2500");
		printf("%s", i == 1 ? "\u252c" : "\u253c");
		for (size_t i; i != end_size + 2; i++)
			printf("%s", "\u2500");
		printf("%s", i == 1 ? "\u252c" : "\u253c");
		for (size_t i; i != state_size + 2; i++)
			printf("%s", "\u2500");
		printf("%s", i == 1 ? "\u2510" : "\u2524");


		/* Print token */
		i++;
	}
	/* Print bot line */
	printf("%s", "\u2514");
	for (size_t i; i != value_size + 2; i++)
		printf("%s", "\u2500");
	printf("%s\n", "\u2534");
	for (size_t i; i != id_size + 2; i++)
		printf("%s", "\u2500");
	printf("%s\n", "\u2534");
	for (size_t i; i != start_size + 2; i++)
		printf("%s", "\u2500");
	printf("%s\n", "\u2534");
	for (size_t i; i != end_size + 2; i++)
		printf("%s", "\u2500");
	printf("%s\n", "\u2534");
	for (size_t i; i != state_size + 2; i++)
		printf("%s", "\u2500");
	printf("%s", "\u2518");
	return (1);
}

int		main(void)
{
	t_list	*token_list;

	t_lexer	lex;
	char	*buff;

	buff = readline("$> ");
	dprintf(2, "%s\n", buff);

	init_lexer(&lex, buff);
	get_token_list(&lex, &token_list, NULL);
	debug_token_list(token_list);
	return (0);
}
