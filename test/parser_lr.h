#ifndef PARSER_LR_H
# define PARSER_LR_H

#define NB_SYMBOLS 47
#define NB_TOKEN 40
#define FIRST_SYMBOL 0
#define FIRST_TOKEN 10000

#define NB_RULES 111

#define IS_TOKEN(i) i >= FIRST_TOKEN && i <= FIRST_TOKEN + NB_TOKEN

#define IS_SYMBOL(i) i >= FIRST_SYMBOL && i <= FIRST_SYMBOL + NB_SYMBOLS
#include "parser.h"
enum e_symbol {
	start_symbol = FIRST_SYMBOL,
	program,
	complete_commands,
	complete_command,
	list,
	and_or,
	pipeline,
	pipe_sequence,
	command,
	compound_command,
	subshell,
	compound_list,
	term,
	for_clause,
	name,
	wordlist,
	case_clause,
	case_list_ns,
	case_list,
	case_item_ns,
	case_item,
	pattern,
	if_clause,
	else_part,
	while_clause,
	until_clause,
	function_definition,
	function_body,
	fname,
	brace_group,
	do_group,
	simple_command,
	cmd_prefix,
	cmd_suffix,
	cmd_name,
	cmd_word,
	redirect_list,
	io_redirect,
	io_file,
	filename,
	io_here,
	here_end,
	newline_list,
	linebreak,
	separator_op,
	separator,
	sequential_sep,
};

enum e_token {
	DOLLAR = FIRST_TOKEN,
	TK_WORD,
	TK_ASSIGNMENT_WORD,
	TK_NAME,
	TK_NEWLINE,
	TK_IO_NUMBER,
	TK_LESS,
	TK_GREAT,
	TK_SEMI,
	TK_PIPE,
	TK_AND,
	TK_AND_IF,
	TK_OR_IF,
	TK_DSEMI,
	TK_DLESS,
	TK_DGREAT,
	TK_LESSAND,
	TK_GREATAND,
	TK_LESSGREAT,
	TK_DLESSDASH,
	TK_CLOBBER,
	TK_IF,
	TK_THEN,
	TK_ELSE,
	TK_ELIF,
	TK_FI,
	TK_DO,
	TK_DONE,
	TK_CASE,
	TK_ESAC,
	TK_WHILE,
	TK_UNTIL,
	TK_FOR,
	TK_LBRACE,
	TK_RBRACE,
	TK_BANG,
	TK_LPAREN,
	TK_RPAREN,
	TK_IN,
	EPSILON,
};

/*
**	a morpheme is a token or a symbol
*/

typedef int t_morpheme;

struct s_morpheme_lst {
	struct s_morpheme_lst	*next;
	t_morpheme				m;
};

struct s_static_grammar_rule {
	t_morpheme		node;
	t_morpheme		childs[7];
};

struct s_grammar_rule {
	t_morpheme				node;
	struct s_morpheme_lst		*childs;
};


/*
**	an item is a [S->ß.Eµ, a]
**	whit a gramar rule, a point and a look ahead symbol
*/

struct s_item {
	struct s_item			*next;
	int					grammar_rule;
	int					point;
	enum e_token		look_ahead;
};

struct s_parser_lr {
	struct s_grammar_rule		grammar_rules[NB_RULES];
	struct s_morpheme_lst		*firsts[NB_SYMBOLS + 2]; //TODO: why 2 ?
};

/*
** in firsts, the indice match the symbol
*/

struct s_line {
	struct s_line			*next;
	int 					state;
	struct s_item			*closure;
	struct s_item			*kernel;
	int						action_table[NB_TOKEN];
	int				 		goto_table[NB_SYMBOLS];
};

void	init_grammar_rules(struct s_parser_lr *lr);
int		get_first_grammar_rule(struct s_grammar_rule *grammar_rule, enum e_symbol symbol) ;
struct s_morpheme_lst *search_morpheme_lst(struct s_morpheme_lst *a, t_morpheme m);
struct s_morpheme_lst *add_unique_morpheme_lst(struct s_morpheme_lst **a, t_morpheme m);
struct s_morpheme_lst *union_morpheme_lst(struct s_morpheme_lst **a, struct s_morpheme_lst *b);
struct s_morpheme_lst	*lr_first(struct s_parser_lr *lr, struct s_morpheme_lst *m_lst);

/*
** debug
*/

void	debug_token(int m);
void	debug_goto_table(struct s_parser_lr *lr, struct s_line *l);
void	debug_line(struct s_parser_lr *lr, struct s_line *l);
void	debug_action_table(struct s_parser_lr *lr, struct s_line *l);
void	debug_symbol(int m);
void	debug_grammar_rule(struct s_parser_lr *lr, int i);
void	debug_gramar(struct s_parser_lr *lr);
void	debug_item_lst(struct s_parser_lr *lr, struct s_item *item);
void	debug_morpheme_lst(struct s_morpheme_lst *lst);
void	debug_morpheme_node(struct s_morpheme_lst *tmp);
void	debug_closure_table(struct s_parser_lr *lr, struct s_line *l);
void	debug_firsts(struct s_parser_lr *lr);

struct s_morpheme_lst	*new_morpheme_lst(t_morpheme m);
struct s_item			*new_item(int grammar_rule, int point, enum e_token token);
struct s_line			*new_line(int state, struct s_item *kernel, struct s_item *closure);
void	init_firsts(struct s_parser_lr *lr);
void	item_pushback_unique(struct s_item **item_lst, int grammar_rule, int point, enum e_token look_ahead);
struct s_morpheme_lst *dup_morpheme_lst(struct s_morpheme_lst *old);
struct s_item *dup_item_lst(struct s_item *old);
#endif
