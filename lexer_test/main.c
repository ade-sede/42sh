#include "libft.h"
#include "lexer.h"
#include "t_lexer.h"
#include <stdio.h>
#include <readline/readline.h>

#ifdef LEXER_DEBUG
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
		token_id_size = ft_strlen(get_id(token->id));
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
	t_token	*token;
	char	*end_str;
	char	*start_str;
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
		printf("%s", i == 1 ? "\u250c" : "\u251c");
		for (size_t i = 0; i != value_size + 2; i++)
			printf("%s", "\u2500");
		printf("%s", i == 1 ? "\u252c" : "\u253c");
		for (size_t i = 0; i != id_size + 2; i++)
			printf("%s", "\u2500");
		printf("%s", i == 1 ? "\u252c" : "\u253c");
		for (size_t i = 0; i != start_size + 2; i++)
			printf("%s", "\u2500");
		printf("%s", i == 1 ? "\u252c" : "\u253c");
		for (size_t i = 0; i != end_size + 2; i++)
			printf("%s", "\u2500");
		printf("%s", i == 1 ? "\u252c" : "\u253c");
		for (size_t i = 0; i != state_size + 2; i++)
			printf("%s", "\u2500");
		printf("%s", i == 1 ? "\u2510" : "\u2524");
		printf("\n");


		/* Print token */

		token = token_list->data;
		end_str = ft_itoa_base(token->state_info[_T_END], 10);
		start_str = ft_itoa_base(token->state_info[_T_START], 10);

		printf("%s", "\u2502");
		printf(" %s", token->value);
		for (int i = value_size - ft_strlen(token->value) + 1; i; --i)
			printf(" ");
		printf("%s", "\u2502");
		printf(" %s", get_id(token->id));
		for (int i = id_size - ft_strlen(get_id(token->id)) + 1; i; --i)
			printf(" ");
		printf("%s", "\u2502");
		printf(" %s", start_str);
		for (int i = start_size - ft_strlen(start_str) + 1; i; --i)
			printf(" ");
		printf("%s", "\u2502");
		printf(" %s", end_str);
		for (int i = end_size - ft_strlen(end_str) + 1; i; --i)
			printf(" ");
		printf("%s", "\u2502");
		printf(" %s", get_state(token->state_info[_T_STATE]));
		for (int i = state_size - ft_strlen(get_state(token->state_info[_T_STATE])) + 1; i; --i)
			printf(" ");
		printf("%s", "\u2502");
		printf("\n");

		free(end_str);
		free(start_str);

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
	for (size_t i = 0; i != start_size + 2; i++)
		printf("%s", "\u2500");
	printf("%s", "\u2534");
	for (size_t i = 0; i != end_size + 2; i++)
		printf("%s", "\u2500");
	printf("%s", "\u2534");
	for (size_t i = 0; i != state_size + 2; i++)
		printf("%s", "\u2500");
	printf("%s\n", "\u2518");
	return (1);
}
#endif

int		main(void)
{
	t_list	*token_list = NULL;

	t_lexer	lex;
	char	*buff;
	size_t	ret;

	buff = readline("$> ");
	dprintf(2, "%s\n", buff);
	buff = ft_strjoin(buff, "\n");
	/* Factioral test */
	/* buff = ft_strchange(buff, ft_strdup(" factorial()\n\n{\nif [ '$1' -gt '1' ]; then\ni=`expr $1 - 1`\nj=`factorial $i`\nk=`expr $1 * $j`\necho $k\nelse\necho 1\nfi\n}\n\nwhile :\ndo\necho 'Enter a number:'\nread x\nfactorial $x\ndone")); */
	buff = ft_strchange(buff, ft_strdup("for a b \n\n\n\n\nin lol"));
	/* dprintf(2, "%s\n", buff); */

	init_lexer(&lex, buff);
	ret = get_token_list(&lex, &token_list, NULL);
#ifdef LEXER_DEBUG
	debug_token_list(token_list);
	printf(PNK"Ret "RESET"%s\n", get_state(ret));
#endif
	while (ret != DEFAULT)
	{
		buff = ft_strchange(buff, ft_strjoin(buff, readline("> ")));
		buff = ft_strjoin(buff, "\n");
		lex.line = ft_strchange(lex.line, buff);
		ret = get_token_list(&lex, &token_list, NULL);
#ifdef LEXER_DEBUG
		debug_token_list(token_list);
		printf(PNK"Ret "RESET"%s\n", get_state(ret));
#endif
	}
	free(buff);

	return (0);
}
