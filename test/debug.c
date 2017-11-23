#include "parser_lr.h"
#include <stdio.h>
struct	s_sym_to_string
{
	int			symbol;
	char			*string;
};
struct s_sym_to_string	sts[] =
{
	{start_symbol,"s'"},
	{s,"s"},
	{c,"c"},
	{0, NULL},
};

void	debug_symbol(int m)
{
	int	i= 0;
	while (sts[i].string)
	{
		if (m == sts[i].symbol)
		{
			printf("%s", sts[i].string);
			return ;
		}
		i++;
	}
	/* debug_token(ast->token); */
	//printf("symbol not found\n");
}

static struct s_sym_to_string g_debug_token_id[] =
{
	{DOLLAR, "DOLLAR"  },
	{E, "E" },
	{F, "F" },
	{EPSILON, "EPSILON" },
	{-1, NULL}
};

void	debug_token(int m)
{
	int	i= 0;
	while (g_debug_token_id[i].string)
	{
		if (m == g_debug_token_id[i].symbol)
		{
			printf("%s", g_debug_token_id[i].string);
			return ;
		}
		i++;
	}
}
