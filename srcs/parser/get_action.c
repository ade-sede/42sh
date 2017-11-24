#include "parser.h"
#include "t_token.h"
#include "automaton.txt"

int token_table[] = {DOLAR,TK_AND,TK_LPAREN,TK_RPAREN,TK_SEMI,TK_LESS,TK_GREAT,TK_AND_IF,TK_ASSIGNMENT_WORD,TK_BANG,TK_CLOBBER,TK_CASE,TK_DGREAT,TK_DLESS,TK_DLESSDASH,TK_DSEMI,TK_DO,TK_DONE,TK_ELIF,TK_ELSE,TK_ESAC,TK_FI,TK_FOR,TK_GREATAND,TK_IO_NUMBER,TK_IF,TK_IN,TK_LESSAND,TK_LESSGREAT,TK_LBRACE,TK_NAME,TK_NEWLINE,TK_OR_IF,TK_RBRACE,TK_THEN,TK_UNTIL,TK_WORD,TK_WHILE,TK_PIPE};

/*
**	l etat acceptant est mis a 10000 arbitrairement et l etat r0 a 4242
*/

int		get_action(t_token *token, int state)
{
	int		col = 0;
	int		line;
	int	nb_col = 39;

//	printf(MAG"#"CYN"%s, %d"MAG"#\n"RESET , token->value, token->id);
	while (col < nb_col && token_table[col] != token->id)
		col++;
	if (col == nb_col && token->id != 42)
	{
//		printf("Eror get action bad token\n");
		return (-1);
	}
	line = state;
	return (g_lr_table[line][col]);
}

/*
**	const static char *rules[112] = {
**		"$accept -> program $end",
**		"program -> linebreak complete_commands linebreak",
**		"program -> linebreak",
**		"complete_commands -> complete_commands newline_list complete_command",
**		"complete_commands -> complete_command",
**		"complete_command -> list separator_op",
**		"complete_command -> list",
**		"list -> list separator_op and_or",
**		"list -> and_or",
**		"and_or -> pipeline",
**		"and_or -> and_or AND_IF linebreak pipeline",
**		"and_or -> and_or OR_IF linebreak pipeline",
**		"pipeline -> pipe_sequence",
**		"pipeline -> Bang pipe_sequence",
**		"pipe_sequence -> command",
**		"pipe_sequence -> pipe_sequence | linebreak command",
**		"command -> simple_command",
**		"command -> compound_command",
**		"command -> compound_command redirect_list",
**		"command -> function_definition",
**		"compound_command -> brace_group",
**		"compound_command -> subshell",
**		"compound_command -> for_clause",
**		"compound_command -> case_clause",
**		"compound_command -> if_clause",
**		"compound_command -> while_clause",
**		"compound_command -> until_clause",
**		"subshell -> ( compound_list )",
**		"compound_list -> linebreak term",
**		"compound_list -> linebreak term separator",
**		"term -> term separator and_or",
**		"term -> and_or",
**		"for_clause -> For name do_group",
**		"for_clause -> For name sequential_sep do_group",
**		"for_clause -> For name linebreak in sequential_sep do_group",
**		"for_clause -> For name linebreak in wordlist sequential_sep do_group",
**		"name -> WORD",
**		"in -> In",
**		"wordlist -> wordlist WORD",
**		"wordlist -> WORD",
**		"case_clause -> Case WORD linebreak in linebreak case_list Esac",
**		"case_clause -> Case WORD linebreak in linebreak case_list_ns Esac",
**		"case_clause -> Case WORD linebreak in linebreak Esac",
**		"case_list_ns -> case_list case_item_ns",
**		"case_list_ns -> case_item_ns",
**		"case_list -> case_list case_item",
**		"case_list -> case_item",
**		"case_item_ns -> pattern ) linebreak",
**		"case_item_ns -> pattern ) compound_list",
**		"case_item_ns -> ( pattern ) linebreak",
**		"case_item_ns -> ( pattern ) compound_list",
**		"case_item -> pattern ) linebreak DSEMI linebreak",
**		"case_item -> pattern ) compound_list DSEMI linebreak",
**		"case_item -> ( pattern ) linebreak DSEMI linebreak",
**		"case_item -> ( pattern ) compound_list DSEMI linebreak",
**		"pattern -> WORD",
**		"pattern -> pattern | WORD",
**		"if_clause -> If compound_list Then compound_list else_part Fi",
**		"if_clause -> If compound_list Then compound_list Fi",
**		"else_part -> Elif compound_list Then compound_list",
**		"else_part -> Elif compound_list Then compound_list else_part",
**		"else_part -> Else compound_list",
**		"while_clause -> While compound_list do_group",
**		"until_clause -> Until compound_list do_group",
**		"function_definition -> fname ( ) linebreak function_body",
**		"function_body -> compound_command",
**		"function_body -> compound_command redirect_list",
**		"fname -> WORD",
**		"brace_group -> Lbrace compound_list Rbrace",
**		"do_group -> Do compound_list Done",
**		"simple_command -> cmd_prefix cmd_word cmd_suffix",
**		"simple_command -> cmd_prefix cmd_word",
**		"simple_command -> cmd_prefix",
**		"simple_command -> cmd_name cmd_suffix",
**		"simple_command -> cmd_name",
**		"cmd_name -> WORD",
**		"cmd_word -> WORD",
**		"cmd_prefix -> io_redirect",
**		"cmd_prefix -> cmd_prefix io_redirect",
**		"cmd_prefix -> ASSIGNMENT_WORD",
**		"cmd_prefix -> cmd_prefix ASSIGNMENT_WORD",
**		"cmd_suffix -> io_redirect",
**		"cmd_suffix -> cmd_suffix io_redirect",
**		"cmd_suffix -> WORD",
**		"cmd_suffix -> cmd_suffix WORD",
**		"redirect_list -> io_redirect",
**		"redirect_list -> redirect_list io_redirect",
**		"io_redirect -> io_file",
**		"io_redirect -> IO_NUMBER io_file",
**		"io_redirect -> io_here",
**		"io_redirect -> IO_NUMBER io_here",
**		"io_file -> < filename",
**		"io_file -> LESSAND filename",
**		"io_file -> > filename",
**		"io_file -> GREATAND filename",
**		"io_file -> DGREAT filename",
**		"io_file -> LESSGREAT filename",
**		"io_file -> CLOBBER filename",
**		"filename -> WORD",
**		"io_here -> DLESS here_end",
**		"io_here -> DLESSDASH here_end",
**		"here_end -> WORD",
**		"newline_list -> NEWLINE",
**		"newline_list -> newline_list NEWLINE",
**		"linebreak -> newline_list",
**		"linebreak ->",
**		"separator_op -> &",
**		"separator_op -> ;",
**		"separator -> separator_op linebreak",
**		"separator -> newline_list",
**		"sequential_sep -> ; linebreak",
**		"sequential_sep -> newline_list",
**	};
*/

static const t_rule	g_rule_table[] = {
	{0, 2},
	{PROGRAM, 3},
	{PROGRAM, 1},
	{COMPLETE_COMMANDS, 3},
	{COMPLETE_COMMANDS, 1},
	{COMPLETE_COMMAND, 2},
	{COMPLETE_COMMAND, 1},
	{LIST, 3},
	{LIST, 1},
	{AND_OR, 1},
	{AND_OR, 4},
	{AND_OR, 4},
	{PIPELINE, 1},
	{PIPELINE, 2},
	{PIPE_SEQUENCE, 1},
	{PIPE_SEQUENCE, 4},
	{COMMAND, 1},
	{COMMAND, 1},
	{COMMAND, 2},
	{COMMAND, 1},
	{COMPOUND_COMMAND, 1},
	{COMPOUND_COMMAND, 1},
	{COMPOUND_COMMAND, 1},
	{COMPOUND_COMMAND, 1},
	{COMPOUND_COMMAND, 1},
	{COMPOUND_COMMAND, 1},
	{COMPOUND_COMMAND, 1},
	{SUBSHELL, 3},
	{COMPOUND_LIST, 2},
	{COMPOUND_LIST, 3},
	{TERM, 3},
	{TERM, 1},
	{FOR_CLAUSE, 3},
	{FOR_CLAUSE, 4},
	{FOR_CLAUSE, 6},
	{FOR_CLAUSE, 7},
	{NAME, 1},
	{SYM_IN, 1},
	{WORDLIST, 2},
	{WORDLIST, 1},
	{CASE_CLAUSE, 7},
	{CASE_CLAUSE, 7},
	{CASE_CLAUSE, 6},
	{CASE_LIST_NS, 2},
	{CASE_LIST_NS, 1},
	{CASE_LIST, 2},
	{CASE_LIST, 1},
	{CASE_ITEM_NS, 3},
	{CASE_ITEM_NS, 3},
	{CASE_ITEM_NS, 4},
	{CASE_ITEM_NS, 4},
	{CASE_ITEM, 5},
	{CASE_ITEM, 5},
	{CASE_ITEM, 6},
	{CASE_ITEM, 6},
	{PATTERN, 1},
	{PATTERN, 3},
	{IF_CLAUSE, 6},
	{IF_CLAUSE, 5},
	{ELSE_PART, 4},
	{ELSE_PART, 5},
	{ELSE_PART, 2},
	{WHILE_CLAUSE, 3},
	{UNTIL_CLAUSE, 3},
	{FUNCTION_DEFINITION, 5},
	{FUNCTION_BODY, 1},
	{FUNCTION_BODY, 2},
	{FNAME, 1},
	{BRACE_GROUP, 3},
	{DO_GROUP, 3},
	{SIMPLE_COMMAND, 3},
	{SIMPLE_COMMAND, 2},
	{SIMPLE_COMMAND, 1},
	{SIMPLE_COMMAND, 2},
	{SIMPLE_COMMAND, 1},
	{CMD_NAME, 1},
	{CMD_WORD, 1},
	{CMD_PREFIX, 1},
	{CMD_PREFIX, 2},
	{CMD_PREFIX, 1},
	{CMD_PREFIX, 2},
	{CMD_SUFFIX, 1},
	{CMD_SUFFIX, 2},
	{CMD_SUFFIX, 1},
	{CMD_SUFFIX, 2},
	{REDIRECT_LIST, 1},
	{REDIRECT_LIST, 2},
	{IO_REDIRECT, 1},
	{IO_REDIRECT, 2},
	{IO_REDIRECT, 1},
	{IO_REDIRECT, 2},
	{IO_FILE, 2},
	{IO_FILE, 2},
	{IO_FILE, 2},
	{IO_FILE, 2},
	{IO_FILE, 2},
	{IO_FILE, 2},
	{IO_FILE, 2},
	{FILENAME, 1},
	{IO_HERE, 2},
	{IO_HERE, 2},
	{HERE_END, 1},
	{NEWLINE_LIST, 1},
	{NEWLINE_LIST, 2},
	{LINEBREAK, 1},
	{LINEBREAK, 0},
	{SEPARATOR_OP, 1},
	{SEPARATOR_OP, 1},
	{SEPARATOR, 2},
	{SEPARATOR, 1},
	{SEQUENTIAL_SEP, 2},
	{SEQUENTIAL_SEP, 1},
};

void	reduce(t_state_lst **state_stack, t_ast_lst **ast_stack, int reduce_rule)
{
	t_rule			rule;
	int				nb_child;
	enum e_symbol	symbol;
	t_ast			*new;
	int				i = 0;

	rule = g_rule_table[reduce_rule];
	nb_child = rule.nb_child;
	symbol = rule.symbol;
//	printf("reduce by rule : %s\n", rules[reduce_rule]);
	new = new_ast(NULL, symbol);
	i = nb_child - 1;
	while (i >= 0)
	{
		ft_genlst_del_one(state_stack, *state_stack, NULL);
		new->child[i] = (*ast_stack)->ast;
		ft_genlst_del_one(ast_stack, *ast_stack,  NULL);
		i--;
	}
	ft_genlst_add(ast_stack, ft_simple_lst_create(new));
}

static const enum e_symbol	g_symbol_table[47] = {AND_OR,BRACE_GROUP,CASE_CLAUSE,CASE_ITEM,CASE_ITEM_NS,CASE_LIST,CASE_LIST_NS,CMD_NAME,CMD_PREFIX,CMD_SUFFIX,CMD_WORD,COMMAND,COMPLETE_COMMAND,COMPLETE_COMMANDS,COMPOUND_COMMAND,COMPOUND_LIST,DO_GROUP,ELSE_PART,FILENAME,FNAME,FOR_CLAUSE,FUNCTION_BODY,FUNCTION_DEFINITION,HERE_END,IF_CLAUSE,SYM_IN,IO_FILE,IO_HERE,IO_REDIRECT,LINEBREAK,LIST,NAME,NEWLINE_LIST,PATTERN,PIPE_SEQUENCE,PIPELINE,PROGRAM,REDIRECT_LIST,SEPARATOR,SEPARATOR_OP,SEQUENTIAL_SEP,SIMPLE_COMMAND,SUBSHELL,TERM,UNTIL_CLAUSE,WHILE_CLAUSE,WORDLIST};

int		get_goto(t_state_lst *state_stack, int reduce_rule)
{
	enum e_symbol	symbol;
	int				col;
	int				res_state;
	int				offset;
	int			symbol_table_len = 47;

	offset = 39;

	symbol = g_rule_table[reduce_rule].symbol;
	res_state = -1;
	col = 0;
	while (col < symbol_table_len)
	{
		if (g_symbol_table[col] == symbol)
			break;
		col++;
	}
	col += offset;
	if ((col == symbol_table_len + offset) || (res_state = g_lr_table[state_stack->state][col]) == -1)
	{
		printf("goto error state -1 \n");
		return (-1);
	}
	return (res_state);
}
