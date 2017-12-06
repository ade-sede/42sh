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
	{program, "program"},
	{complete_commands, "complete_commands"},
	{complete_command, "complete_command"},
	{list, "list"},
	{and_or, "and_or"},
	{pipeline, "pipeline"},
	{pipe_sequence, "pipe_sequence"},
	{command, "command"},
	{compound_command, "compound_command"},
	{subshell, "subshell"},
	{compound_list, "compound_list"},
	{term, "term"},
	{for_clause, "for_clause"},
	{name, "name"},
	{wordlist, "wordlist"},
	{case_clause, "case_clause"},
	{case_list_ns, "case_list_ns"},
	{case_list, "case_list"},
	{case_item_ns, "case_item_ns"},
	{case_item, "case_item"},
	{pattern, "pattern"},
	{if_clause, "if_clause"},
	{else_part, "else_part"},
	{while_clause, "while_clause"},
	{until_clause, "until_clause"},
	{function_definition, "function_definition"},
	{function_body, "function_body"},
	{fname, "fname"},
	{brace_group, "brace_group"},
	{do_group, "do_group"},
	{simple_command, "simple_command"},
	{cmd_prefix, "cmd_prefix"},
	{cmd_suffix, "cmd_suffix"},
	{cmd_name, "cmd_name"},
	{cmd_word, "cmd_word"},
	{redirect_list, "redirect_list"},
	{io_redirect, "io_redirect"},
	{io_file, "io_file"},
	{filename, "filename"},
	{io_here, "io_here"},
	{here_end, "here_end"},
	{newline_list, "newline_list"},
	{linebreak, "linebreak"},
	{separator_op, "separator_op"},
	{separator, "separator"},
	{sequential_sep, "sequential_sep"},
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
	{TK_WORD, "TK_WORD" },
	{TK_ASSIGNMENT_WORD, "TK_ASSIGNMENT_WORD" },
	{TK_NAME, "TK_NAME" },
	{TK_NEWLINE, "TK_NEWLINE" },
	{TK_IO_NUMBER, "TK_IO_NUMBER" },
	{TK_LESS, "TK_LESS" },
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

void		debug_grammar_rule(struct s_parser_lr *lr, int i) 
{
	struct s_morpheme_lst	*childs;
	childs = lr->grammar_rules[i].childs;
	debug_symbol(lr->grammar_rules[i].node);
	printf("-> ");
	if (!childs)
		printf("no_childs");
	while (childs)
	{
		if (IS_TOKEN(childs->m))
			debug_token(childs->m);
		else if (IS_SYMBOL(childs->m))
			debug_symbol(childs->m);
		else
		{
			printf("invalid symbol");
			break;
		}
//		printf("child i is : %d", childs->m);
		printf(" ");
		childs = childs->next;
	}
	printf("\n");
}

void	debug_gramar(struct s_parser_lr *lr)
{
	int	i = 0;
	
	while (i < NB_RULES)
	{
		debug_grammar_rule(lr, i);
		i++;
	}
}

void	debug_firsts(struct s_parser_lr *lr)
{
	int	i = FIRST_SYMBOL;

	while (i < NB_SYMBOLS)
	{
		printf("----------\n");
		struct s_morpheme_lst	*childs;
		childs = lr->firsts[i].lst;
		debug_symbol(i); printf(":");
		printf(" nullable :%d\n", lr->firsts[i].nullable);
		while (childs)
		{
			if (IS_TOKEN(childs->m))
				debug_token(childs->m);
			else if (IS_SYMBOL(childs->m))
				debug_symbol(childs->m);
			else
			{
				printf("invalid symbol");
				break;
			}
			//		printf("child i is : %d", childs->m);
			printf(" ");
			childs = childs->next;
		}
		i++;
		printf("\n");
	}
}
void	debug_morpheme_node(struct s_morpheme_lst *tmp)
{
		if (IS_TOKEN(tmp->m))
			debug_token(tmp->m);
		else if (IS_SYMBOL(tmp->m))
			debug_symbol(tmp->m);
		else
			printf("invalid symbol");
		printf(" ");
}

void	debug_morpheme_lst(struct s_morpheme_lst *tmp)
{
	while (tmp)
	{
		debug_morpheme_node(tmp);
		tmp = tmp->next;
	}
	printf("\n");
}

void	debug_item(struct s_parser_lr *lr, struct s_item *item)
{
	int		i = 0;

	printf("{[");
	struct s_morpheme_lst	*childs;
	childs = lr->grammar_rules[item->grammar_rule].childs;
	debug_symbol(lr->grammar_rules[item->grammar_rule].node);
	printf("-> ");
	if (!childs)
		printf("no_childs");
	while (childs)
	{
		if (i == item->point)
			printf(".");
		if (IS_TOKEN(childs->m))
			debug_token(childs->m);
		else if (IS_SYMBOL(childs->m))
			debug_symbol(childs->m);
		else
		{
			printf("invalid symbol");
			break;
		}
		//		printf("child i is : %d", childs->m);
		printf(" ");
		childs = childs->next;
		i++;
	}
	if (i == item->point)
		printf(".");
	printf(", ");
	debug_token(item->look_ahead);
	printf("]}; ");
}

void	debug_item_lst(struct s_parser_lr *lr, struct s_item *item)
{
	while (item)
	{
		debug_item(lr, item);
		item = item->next;
	}
}

void	debug_line(struct s_parser_lr *lr, struct s_line *l)
{
	printf("\nkernel:");
	debug_item_lst(lr, l->kernel);
	printf("\nclosure");
	debug_item_lst(lr, l->closure);
	printf("\n----------");
}

void	debug_closure_table(struct s_parser_lr *lr, struct s_line *l)
{
	printf("---------debug_closure_table----------");
	while (l)
	{
		debug_line(lr, l);
		l = l->next;
	}
}

void	debug_action_table(struct s_parser_lr *lr, struct s_line *l)
{
    int i = 0;
    int state_nbr = 0;
	printf("---------debug_action_table----------\n");
    while (i < NB_TOKEN)
    {
        debug_token(i + FIRST_TOKEN);
        printf(" ");
        i++;
    }
    printf("\n");
	while (l)
	{
		int	i = 0;
        printf("%d ", state_nbr);
		while (i < NB_TOKEN)
		{
			if (l->action_table[i] == acc)
				printf("acc ");
			else if (l->action_table[i] >= 4242)
				printf("r%d ", l->action_table[i] - 4242);
			else if (l->action_table[i] == -1)
				printf("%d ", -1);
			else 
				printf("s%d ", l->action_table[i]);
			i++;
		}
		printf("\n");
		l = l->next;
		state_nbr++;
	}
}

void	debug_goto_table(struct s_parser_lr *lr, struct s_line *l)
{
	printf("---------debug_goto_table----------\n");
    int i = 0;
	printf("---------debug_action_table----------\n");
    while (i < NB_SYMBOLS)
    {
        debug_symbol(i + FIRST_SYMBOL);
        printf(" ");
        i++;
    }
    printf("\n");
	while (l)
	{
		int	i = 0;
		while (i < NB_SYMBOLS)
		{
			printf("%d ", l->goto_table[i]);
			i++;
		}
		printf("\n");
		l = l->next;
	}
}
