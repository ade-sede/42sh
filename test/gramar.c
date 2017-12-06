#include "parser_lr.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static struct s_static_grammar_rule rules[NB_RULES] = {

	{start_symbol, {program, DOLLAR}},
	{program, {linebreak, complete_commands, linebreak}},
	{program, {linebreak}},
	{complete_commands, {complete_commands, newline_list, complete_command}},
	{complete_commands, {complete_command}},
	{complete_command, {list, separator_op}},
	{complete_command, {list}},
	{list, {list, separator_op, and_or}},
	{list, {and_or}},
	{and_or, {pipeline}},
	{and_or, {and_or, TK_AND_IF, linebreak, pipeline}},
	{and_or, {and_or, TK_OR_IF, linebreak, pipeline}},
	{pipeline, {pipe_sequence}},
	{pipeline, {TK_BANG, pipe_sequence}},
	{pipe_sequence, {command}},
	{pipe_sequence, {pipe_sequence, TK_PIPE, linebreak, command}},
	{command, {simple_command}},
	{command, {compound_command}},
	{command, {compound_command, redirect_list}},
	{command, {function_definition}},
	{compound_command, {brace_group}},
	{compound_command, {subshell}},
	{compound_command, {for_clause}},
	{compound_command, {case_clause}},
	{compound_command, {if_clause}},
	{compound_command, {while_clause}},
	{compound_command, {until_clause}},
	{subshell, {TK_LPAREN, compound_list, TK_RPAREN}},
	{compound_list, {linebreak, term}},
	{compound_list, {linebreak, term, separator}},
	{term, {term, separator, and_or}},
	{term, {and_or}},
	{for_clause, {TK_FOR, name, do_group}},
	{for_clause, {TK_FOR, name, sequential_sep, do_group}},
	{for_clause, {TK_FOR, name, linebreak, TK_IN, sequential_sep, do_group}},
	{for_clause, {TK_FOR, name, linebreak, TK_IN, wordlist, sequential_sep, do_group}},
	{name, {TK_NAME}},
	{wordlist, {wordlist, TK_WORD}},
	{wordlist, {TK_WORD}},
	{case_clause, {TK_CASE, TK_WORD, linebreak, TK_IN, linebreak, case_list, TK_ESAC}},
	{case_clause, {TK_CASE, TK_WORD, linebreak, TK_IN, linebreak, case_list_ns, TK_ESAC}},
	{case_clause, {TK_CASE, TK_WORD, linebreak, TK_IN, linebreak, TK_ESAC}},
	{case_list_ns, {case_list, case_item_ns}},
	{case_list_ns, {case_item_ns}},
	{case_list, {case_list, case_item}},
	{case_list, {case_item}},
	{case_item_ns, {pattern, TK_RPAREN, linebreak}},
	{case_item_ns, {pattern, TK_RPAREN, compound_list}},
	{case_item_ns, {TK_LPAREN, pattern, TK_RPAREN, linebreak}},
	{case_item_ns, {TK_LPAREN, pattern, TK_RPAREN, compound_list}},
	{case_item, {pattern, TK_RPAREN, linebreak, TK_DSEMI, linebreak}},
	{case_item, {pattern, TK_RPAREN, compound_list, TK_DSEMI, linebreak}},
	{case_item, {TK_LPAREN, pattern, TK_RPAREN, linebreak, TK_DSEMI, linebreak}},
	{case_item, {TK_LPAREN, pattern, TK_RPAREN, compound_list, TK_DSEMI, linebreak}},
	{pattern, {TK_WORD}},
	{pattern, {pattern, TK_PIPE, TK_WORD}},
	{if_clause, {TK_IF, compound_list, TK_THEN, compound_list, else_part, TK_FI}},
	{if_clause, {TK_IF, compound_list, TK_THEN, compound_list, TK_FI}},
	{else_part, {TK_ELIF, compound_list, TK_THEN, compound_list}},
	{else_part, {TK_ELIF, compound_list, TK_THEN, compound_list, else_part}},
	{else_part, {TK_ELSE, compound_list}},
	{while_clause, {TK_WHILE, compound_list, do_group}},
	{until_clause, {TK_UNTIL, compound_list, do_group}},
	{function_definition, {fname, TK_LPAREN, TK_RPAREN, linebreak, function_body}},
	{function_body, {compound_command}},
	{function_body, {compound_command, redirect_list}},
	{fname, {TK_NAME}},
	{brace_group, {TK_LBRACE, compound_list, TK_RBRACE}},
	{do_group, {TK_DO, compound_list, TK_DONE}},
	{simple_command, {cmd_prefix, cmd_word, cmd_suffix}},
	{simple_command, {cmd_prefix, cmd_word}},
	{simple_command, {cmd_prefix}},
	{simple_command, {cmd_name, cmd_suffix}},
	{simple_command, {cmd_name}},
	{cmd_name, {TK_WORD}},
	{cmd_word, {TK_WORD}},
	{cmd_prefix, {io_redirect}},
	{cmd_prefix, {cmd_prefix, io_redirect}},
	{cmd_prefix, {TK_ASSIGNMENT_WORD}},
	{cmd_prefix, {cmd_prefix, TK_ASSIGNMENT_WORD}},
	{cmd_suffix, {io_redirect}},
	{cmd_suffix, {cmd_suffix, io_redirect}},
	{cmd_suffix, {TK_WORD}},
	{cmd_suffix, {cmd_suffix, TK_WORD}},
	{redirect_list, {io_redirect}},
	{redirect_list, {redirect_list, io_redirect}},
	{io_redirect, {io_file}},
	{io_redirect, {TK_IO_NUMBER, io_file}},
	{io_redirect, {io_here}},
	{io_redirect, {TK_IO_NUMBER, io_here}},
	{io_file, {TK_LESS, filename}},
	{io_file, {TK_LESSAND, filename}},
	{io_file, {TK_GREAT, filename}},
	{io_file, {TK_GREATAND, filename}},
	{io_file, {TK_DGREAT, filename}},
	{io_file, {TK_LESSGREAT, filename}},
	{io_file, {TK_CLOBBER, filename}},
	{filename, {TK_WORD}},
	{io_here, {TK_DLESS, here_end}},
	{io_here, {TK_DLESSDASH, here_end}},
	{here_end, {TK_WORD}},
	{newline_list, {TK_NEWLINE}},
	{newline_list, {newline_list, TK_NEWLINE}},
	{linebreak, {newline_list}},
	{linebreak, {0}},
	{separator_op, {TK_AND}},
	{separator_op, {TK_SEMI}},
	{separator, {separator_op, linebreak}},
	{separator, {newline_list}},
	{sequential_sep, {TK_SEMI, linebreak}},
	{sequential_sep, {newline_list}},
};

void	init_grammar_rules(struct s_parser_lr *lr)
{
	int	i = 0;

	while (i < NB_RULES)
	{
		lr->grammar_rules[i].node = rules[i].node;
		int	j = 0;
		lr->grammar_rules[i].childs = NULL;
		/* > 0 is safe because start_symbol = 0 and cant be a child */
		while (j < 7 && rules[i].childs[j] > 0)
		{
			ft_genlst_pushback((void **)&lr->grammar_rules[i].childs, new_morpheme_lst(rules[i].childs[j]));
			j++;
		}
		i++;
	}
}

int		get_first_grammar_rule(struct s_grammar_rule *grammar_rule, enum e_symbol symbol) 
{
	int		i;

	i = 0;
	while (i < NB_RULES)
	{
		if (grammar_rule[i].node == symbol)
			return (i);
		i++;
	}
	return (-1);
}
